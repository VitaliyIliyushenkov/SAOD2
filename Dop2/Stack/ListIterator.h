#include "LNode.h"

template <typename T>
class ListIterator {
public:
    LNode<T>* current;

    ListIterator(LNode<T>* current) : current(current) {}

    T& operator*() {
        return current->value;
    }

    ListIterator<T>& operator++() {
        current = current->next;
        return *this;
    }

    ListIterator<T>& operator--() {
        current = current->prev;
        return *this;
    }

    bool operator==(const ListIterator<T>& other) const {
        return current == other.current;
    }

    bool operator!=(const ListIterator<T>& other) const {
        return !(*this == other);
    }
};