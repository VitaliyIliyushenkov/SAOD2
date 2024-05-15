#include <iostream>
#include "Test.h"

class Aggregate
{
    private:
        Test m_objTest;

    public:
        Aggregate() {
            std::cout << "Constructor of Aggregate" << std::endl;
        }

        ~Aggregate() {
            std::cout << "Destructor of Aggregate" << std::endl;
        }
};

