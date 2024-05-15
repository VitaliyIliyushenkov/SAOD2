#include "stdafx.h"
#include "Codec.h"


void Codec::outputCode(ofstream &os, const HC::Code &c)
{
	static unsigned char cBuffer;		// для хранения остатков предыдущего кода
	static int iNumberOfBitsInBuffer;	// для хранения длины остатка в битах

	// Собственно кодирование
	if (c.len > 0) {
		int iCode = c.bits;
		unsigned int selector = 1 << (c.len - 1);
		while(selector != 0)
		{
			// Помещаем в буфер биты входного кода
			cBuffer <<= 1;
			cBuffer += (selector&iCode) != 0? 1:0;
			selector >>= 1;
			iNumberOfBitsInBuffer++;
			// Если заполнен байт, то пишем его в выходной поток, сбрасываем буфер и начинаем накапливать следующий байт
			if (iNumberOfBitsInBuffer == 8) {
				os.put(cBuffer);
				cBuffer = (unsigned char)0;
				iNumberOfBitsInBuffer = 0;
			}
		}
	}
	// Пишем в поток последний код (остатки битов) и последний байт - количество битов в последнем байте
	else 
	{
		if (iNumberOfBitsInBuffer != 0)
		{
			os.put(cBuffer << (8 - iNumberOfBitsInBuffer));
			os.put((char)(iNumberOfBitsInBuffer));
		}
		else
			os.put(8);
	}
}


bool Codec::getBit(ifstream &is, int &bit)
{
	static bool init = true;
	static char last;
	static char buff;
	static unsigned char mask;

 	if (init)
	{
		init = false;
		is.get(last);
	}
	// Читаем следующий байт
	if (mask == 0 && !is.eof())
	{
		buff = last;
		is.get(last);
		mask = 0x80;	// старший бит байта
	}
	
	// Последний байт уже прочтен. В нем количество значимых битов в предыдущем байте
	if (is.peek() == EOF)
		if (last > 0) // добираем неполный байт
		{
			bit = (mask&buff) != 0 ? 1 : 0;
			mask >>= 1;				// перейдем к следующему биту
			last--;
			return true;
		}
		else
			return false;

	bit = (mask&buff) != 0 ? 1 : 0;
	mask >>= 1;				// перейдем к следующему биту
	return true;
}

int Codec::CompressFile(ifstream& is, ofstream& os)
{
	map<char, int> chTbl;
	unsigned char chCurrent;
	is.get((char&)chCurrent);
	while (!is.eof())
	{
		chTbl[chCurrent]++;
		is.get((char&)chCurrent);
	}

	/// Геннерация кодов Хаффмана
	HC hc;
	hc.GenerateCodes(chTbl);

	/// Подготовка вывода в поток таблицы кодов
	int n = 0;
	for (int i = 0; i < hc.TblSize(); i++)
		if (hc.GetCode(i).len)
			n++;

	// Вывод таблицы кодов в файл
	// int n - количество записей в таблице
	// {ch, len, code} по числу записей
	os.write((char*)&n, sizeof(n));
	for (int i = 0; i < hc.TblSize(); i++) {
		HC::Code c = hc.GetCode(i);
		if (c.len != 0)
		{
			os.put(c.ch);
			os.put(c.len);
			os.write((char*)&c.bits, sizeof(c.bits));
		}
	}

	/// Повтороное чтение входного потока и его кодирование
	is.clear();
	is.seekg(0, ios::beg);

#ifdef WITH_BLOCKS
	auto r = Analyze(is);

	is.clear();
	is.seekg(0, ios::beg);

	int blockLen = 0;
	int nBlk = 0;

	auto rit = r.begin();		// Итератор для списка повторов
	int pos = 0, bbPos=0;		// Позиция в файле и позиция начала блока
	is.get((char&)chCurrent);
	while (!is.eof())
	{
		if (rit != r.end() && rit->second > 0)
		{
			if (pos < rit->first &&  bbPos < MAX_BLOCK_LEN)	//кодируем по Хаффману
			{
				if(bbPos++ == 0)	// Выводим заголовок блока кодов по Хаффману и считаем длину блока
					outputCode(os, MakeCode(rit->first - pos));

				outputCode(os, hc.GetCode(chCurrent));
			}
			else if (pos == rit->first) // Выводим заголовок для RLE
			{
				outputCode(os, MakeCode(rit->second, chCurrent));
			}
			if (pos + 1 == rit->first + rit->second) {		// Начинаем блок кодов Хаффмана
				rit++;										// читаем описание следующего повтора.
				bbPos = 0;									// Сбрасываем начало блока по Хаффману.
			}
		}
		else {					// Больше блоков RLE нет
			if (bbPos++ == 0 && rit != r.end()) {			// Выводим заголовок блока кодов по Хаффману
				outputCode(os, MakeCode(rit->first - pos));	// Нужно знать сколько кодов до конца!
			}
			outputCode(os, hc.GetCode(chCurrent));
		}

		is.get((char&)chCurrent);
		pos++;
	}
	outputCode(os, HC::Code(0, 0));
#else
	is.get((char&)chCurrent);
	while (!is.eof())
	{
		outputCode(os, hc.GetCode((unsigned char)chCurrent));
		is.get((char&)chCurrent);
	}
	outputCode(os, HC::Code(0, 0));
#endif
	return 0;
}

int Codec::DeCompressFile(ifstream &is, ofstream &os) {
	int n;
	is.read((char*)&n, sizeof(n));

	// Создаем таблицу кодов
	HC hc;
	for (int i = 0; i < n; i++) {
		HC::Code c;
		is.get((char&)c.ch);
		is.get((char&)c.len);
		is.read((char*)&c.bits, sizeof(c.bits));
		hc.SetCode(c);
	}

	// Восстанавливаем дерево Хаффмана
	shared_ptr<HC::SimpleNode> root = hc.ReconstructTree();

	// Декодируем данные
	int bit;
	shared_ptr<HC::SimpleNode> current = root;
	while (getBit(is, bit)) {
		if (bit == 1) {
			current = current->right;
		}
		else {
			current = current->left;
		}

		if (current->IsLeave()) {
			os.put(current->ch);
			current = root;
		}
	}

	return 0;
}
