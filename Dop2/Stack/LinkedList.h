template <typename T>
struct ILinkedList
{
    virtual void push_back(const T& data) = 0, push_front(const T& data) = 0;
    virtual void pop_back() = 0, pop_front() = 0;
    virtual T front() const = 0, back() const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual ~ILinkedList() {}
};

template <typename T>
class LinkedList : public ILinkedList<T>
{
public:

    LinkedList() : head(new LNode<T>()), tail(new LNode<T>()) {
        head->next = tail;
        tail->prev = head;
    }
    LinkedList(const LinkedList& other) {
        *this = other;
    }
    LinkedList(LinkedList&& other) noexcept {
        *this = std::move(other);
    }
    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) {
            return *this;
        }
        clear();
        LNode<T>* current = other.head->next;
        while (current != other.tail) {
            push_back(current->value);
            current = current->next;
        }
        return *this;
    }
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
        return *this;
    }
    ~LinkedList() {
        clear();
        delete head;
        delete tail;
    }

    // ���������� �������� � ����� ������.
    void push_back(const T& value) {
        LNode<T>* new_LNode = new LNode<T>(value);
        new_LNode->prev = tail->prev;
        tail->prev->next = new_LNode;
        new_LNode->next = tail;
        tail->prev = new_LNode;
        ++size_;
    }

    // ���������� �������� � ������ ������.
    void push_front(const T& value) {
        LNode<T>* new_LNode = new LNode<T>(value);
        new_LNode->next = head->next;
        head->next->prev = new_LNode;
        new_LNode->prev = head;
        head->next = new_LNode;
        ++size_;
    }

    //���������� ��-�� �� �������
    void insert(size_t idx, const T& value) {
        if (idx == 0) {
            push_front(value);
        }
        else if (idx == size_) {
            push_back(value);
        }
        else {
            LNode<T>* new_LNode = new LNode<T>(value);
            LNode<T>* current = head->next;
            for (size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            new_LNode->prev = current->prev;
            current->prev->next = new_LNode;
            new_LNode->next = current;
            current->prev = new_LNode;
            ++size_;
        }
    }

    // �������� ���������� �������� �� ������.
    void pop_back() {
        if (size_ == 0) {
            return;
        }
        LNode<T>* LNode_to_delete = tail->prev;
        tail->prev = LNode_to_delete->prev;
        LNode_to_delete->prev->next = tail;
        delete LNode_to_delete;
        --size_;
    }

    // �������� ������� �������� �� ������
    void pop_front() {
        if (size_ == 0) {
            return;
        }
        LNode<T>* LNode_to_delete = head->next;
        head->next = LNode_to_delete->next;
        LNode_to_delete->next->prev = head;
        delete LNode_to_delete;
        --size_;
    }

    // �������� ��-�� �� �������
    void remove_at(size_t idx) {
        if (idx == 0) {
            pop_front();
        }
        else if (idx == size_ - 1) {
            pop_back();
        }
        else {
            LNode<T>* current = head->next;
            for (size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            --size_;
        }
    }

    // ��� ������ ��-�� �� ���������� �������
    T& operator[](const size_t index) {
        if (index >= size_) {
            throw std::out_of_range("The index is outside the list.");
        }
        LNode<T>* current = head->next;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    // ��� ������ �� �������
    const T& operator[](const size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("The index is outside the list..");
        }
        LNode<T>* current = head->next;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    // ���������� ���-�� ��-�� � ������
    size_t size() const {
        return size_;
    }

    // �������� �� ������ ������ �� ������
    bool empty() const {
        return size_ == 0;
    }

    // ������� ������, ������ ��� ����
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    // ������ � ������� ��������.
    T front() const {
        if (size_ == 0) {
            throw std::runtime_error("������ ����.");
        }
        return head->next->value;
    }

    // ������ � ���������� ��������.
    T back() const {
        if (size_ == 0) {
            throw std::runtime_error("������ ����.");
        }
        return tail->prev->value;
    }

    ListIterator<T> begin() {
        return ListIterator<T>(head);
    }

    ListIterator<T> end() {
        return ListIterator<T>(nullptr);
    }

private:
    LNode<T>* head;
    LNode<T>* tail;
    size_t size_ = 0;
};