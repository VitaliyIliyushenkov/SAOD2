template <typename T>
class LNode {
public:
    LNode() : value(0), next(nullptr) {}
    LNode(const T& value) : value(value), next(nullptr) {}
    T value;
    //LNode<T>* prev;
    LNode<T>* next;
};
