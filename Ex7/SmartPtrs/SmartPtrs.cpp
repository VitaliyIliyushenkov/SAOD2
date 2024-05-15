// SmartPtrs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <memory>
#include "Test.h"
using namespace std;

shared_ptr<Test> foo() {
    shared_ptr<Test> test = make_shared<Test>();

    test->intVal = 42;

    return test;
}

Test* goo() {
    Test* test = new Test();

    test->intVal = 42;

    return test;
}

int main()
{
    /*auto p = foo();
    cout << "Value intVal: " << p->intVal << endl;

    Test* p = goo();
    cout << "Value intVal: " << p->intVal << endl;
    delete p;*/

    shared_ptr<Test> t;
    {
        shared_ptr<Test> p = foo();
        cout << "Value intVal: " << p->intVal << endl;
        t = p;
    }

    cout << "afterblock" << endl;

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
