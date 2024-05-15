// LWF.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include "WF.h"
#include "WFOpt.h"
using namespace std;

int main()
{
    WF wf;
    wf.Init("no", "ono");

    cout << "Matrix:" << endl;
    for (int i = 0; i < wf.intRows(); i++) {
        for (int j = 0; j < wf.intColumns(); j++) {
            cout << wf.intGet(i, j) << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Number of lines: " << wf.intRows() << endl;
    cout << "Number of columns: " << wf.intColumns() << endl;
    cout << "The distance between the lines: " << wf.intDistance() << endl;
    int distance_opt = Distance("no", "ono");
    cout << "Distance by optimized function: " << distance_opt << endl;
    
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
