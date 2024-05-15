#include <iostream>
class Test {
public:
    static int nCount;
    Test(const Test& other) {
        nCount++;
        std::cout << "Object copied. nCount = " << nCount << std::endl;
    }
    Test() {
        nCount++;
        std::cout << "Object created. nCount = " << nCount << std::endl;
    }
    ~Test() {
        nCount--;
        std::cout << "Object destroyed. nCount = " << nCount << std::endl;
    }
};




