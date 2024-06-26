template <typename T>
class LinkedList {
public:

    LinkedList() : head(new LNode<T>()), tail(new LNode<T>()) {
        head->next = tail;
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
        LNode<T>* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        new_LNode->next = tail;
        current->next = new_LNode;
        ++size_;
    }

    // ���������� �������� � ������ ������.
    void push_front(const T& value) {
        LNode<T>* new_LNode = new LNode<T>(value);
        new_LNode->next = head->next;
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
            LNode<T>* current = head;
            for (size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            new_LNode->next = current->next;
            current->next = new_LNode;
            ++size_;
        }
    }

    // �������� ���������� �������� �� ������.
    void pop_back() {
        if (size_ == 0) {
            return;
        }
        LNode<T>* current = head;
        while (current->next->next != tail) {
            current = current->next;
        }
        LNode<T>* LNode_to_delete = current->next;
        current->next = tail;
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
            LNode<T>* current = head;
            for (size_t i = 0; i < idx; ++i) {
                current = current->next;
            }
            LNode<T>* LNode_to_delete = current->next;
            current->next = LNode_to_delete->next;
            delete LNode_to_delete;
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
        LNode<T>* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        return current->value;
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