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

template <typename T>
struct IStack {
    virtual void push(const T& data) = 0;
    virtual void pop() = 0;
    virtual T top() const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IStack() {}
};

template <typename T>
class Stack : public LinkedList<T>, public IStack<T> {
public:
    Stack() : LinkedList<T>() {}

    void push(const T& data) override {
        LinkedList<T>::push_front(data);
    }

    void pop() override {
        LinkedList<T>::pop_front();
    }

    T top() const override {
        return LinkedList<T>::front();
    }

    size_t size() const override {
        return LinkedList<T>::size();
    }

    bool empty() const override {
        return LinkedList<T>::empty();
    }

    ~Stack() {}
};

int main() {
    Stack<char> st;
    st.push('a');
    st.push('b');
    st.push('c');

    std::cout << st.size() << std::endl;

    Stack<char> s;
    s = st;

    while (!st.empty()) {
        std::cout << st.top() << '\t';
        st.pop();
    }
    std::cout << std::endl;
    std::cout << st.size() << '\t' << s.size()
        << '\t' << s.top() << std::endl;

    return 0;
}