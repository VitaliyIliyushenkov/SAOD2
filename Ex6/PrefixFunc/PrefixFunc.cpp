// PrefixFunc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include "PF.h"

int main()
{
    const char* inputString = "rakaratrakarakarakatakarakara";

    PF prefixFunction;
    prefixFunction.Init(inputString);

    cout << "Array length: " << static_cast<int>(prefixFunction) << endl;

    for (int i = 0; i < static_cast<int>(prefixFunction); ++i) {
        cout << prefixFunction[i];
    }
    cout << endl;

    const int N = 50;
    char s[N]{ 0 };
    for (int i = 0; i < N - 1; i++) {
        cout << i;
        s[i] = rand() % ('c' - 'a') + 'a';
    }
        

    PF prefixFunction2;
    prefixFunction2.Init(s);

    cout << "The number of comparisons: " << prefixFunction2.intCmpCount() << endl;

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
