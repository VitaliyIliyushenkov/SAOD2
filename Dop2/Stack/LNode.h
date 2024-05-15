template <typename T>
class LNode {
public:
    LNode() : value(0), prev(nullptr), next(nullptr) {}
    LNode(const T& value) : value(value), prev(nullptr), next(nullptr) {}

    T value;
    LNode<T>* prev;
    LNode<T>* next;
};
