// classes.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "complex.h"
using namespace std;

int main() {
    Complex c(3.5, 5.2); 
    cout << c << endl;

    Complex a(1, 2), b = 5, n;
    cout << a << ", " << b << ", " << n << endl;

    cout << c - c << endl;
    cout << c / c << endl;
    cout << c.ComplexConjugate() << endl;

    cout << a.doubleMod() << endl;
    cout << b.Arg() << endl;
    cout << c.Arg() << endl;

    Complex arr[4];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = Complex(3,4);
    arr[3] = b;

    for (int i = 0; i < 4; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    Complex v[4]{ 1, 2, Complex(3, 4), b };
    for (int i = 0; i < 4; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;

    Complex* pc,* pc2, *pc3;
    pc = new Complex(7,6);
    pc2 = new Complex();
    pc3 = new Complex(1, 2);

    cout << *pc << ", "<< *pc2 << ", " << *pc3 << endl;
    cout <<"Re:"<<pc->Re<<", Im:"<<pc->Im<< endl;

    delete pc;

    Complex* complex_arr = new Complex[4]{ 1,2,3,4 };
    cout << complex_arr[1].Re << endl;

    delete[] complex_arr;
    
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
