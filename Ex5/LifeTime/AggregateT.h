template <class T>
class AggregateT {
public:
    AggregateT() {
        std::cout << "AggregateT constructor called" << std::endl;
    }

    ~AggregateT() {
        std::cout << "AggregateT destructor called" << std::endl;
    }
};