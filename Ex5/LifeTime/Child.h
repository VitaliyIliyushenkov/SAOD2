#include <iostream>
#include "Test.h"

class Child : public Test
{
    public:
        Child() {
            nCount++;
            std::cout << "Constructor of Child" << nCount << std::endl;
        }

        ~Child() {
            nCount--;
            std::cout << "Destructor of Child" << nCount << std::endl;
        }
};

