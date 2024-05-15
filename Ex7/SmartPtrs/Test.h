using namespace std;


class Test {
public:
    Test() {
        cout << "The Test constructor is completed" << endl;
        intVal = 0;
    }
    ~Test() {
        cout << "The Test destructor is executed" << endl;
    }

    int intVal;
};
