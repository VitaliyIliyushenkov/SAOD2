#include <iostream>
#include <numeric>
#include "ListIterator.h"
#include "LinkedList.h"


using namespace std;

template <typename T>
void print_lst(LinkedList<T>& lst) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it;
    }
    std::cout << '\n';
}

int main() {
    // Создание списка. Не получилось задать список через {}
    LinkedList<int> l;
    l.push_back(3);
    l.push_back(5);
    l.push_back(2);
    l.push_back(7);
    l.push_back(8);

    // Сумма элементов с использованием range-based for.
    int s = 0;
    for (auto& i : l) {
        s += i * 10;
    }

    // Сумма элементов с использованием лямбда-функции и accumulate.
    auto lambda = [](int a, int b) { return a + b * 10; };
    cout << s << '\t' << std::accumulate(l.begin(), l.end(), 0, lambda) << '\n';


    LinkedList <char> lst;
    std::cout << std::boolalpha << lst.empty() << std::endl;
    for (int i = 0; i < 5; i++)
        lst.push_back(char('a' + i));

    print_lst(lst);

    for (int i = 0; i < 5; i++)
        lst.insert(0, char('z' - i));
    
    print_lst(lst);

    for (size_t i = 0; i != lst.size(); i++)
        lst[i] = char('a' + i);
    print_lst(lst);
 
    lst.pop_back();
    lst.pop_front();

    print_lst(lst);

    lst.remove_at(5);
    lst.insert(3, 'o');
    
    print_lst(lst);
    
    lst.clear();

    lst.push_back('q');
    lst.push_back('w');
    std::cout << lst.size() << ' ' << std::boolalpha << lst.empty() << std::endl;
    
    return 0;
}