#include <iostream>
#include <cmath>
using namespace std;

class Complex {
public:
    double Re, Im;

    Complex(double re = 0, double im = 0) : Re(re), Im(im) {} // �����������

    //�������� ��� Complex

    Complex operator +(const Complex& c) const
    {
        return Complex(Re + c.Re, Im + c.Im);
    }

    Complex operator -(const Complex& c) const
    {
        return Complex(Re - c.Re, Im - c.Im);
    }

    Complex operator *(const Complex& c) const
    {
        return Complex(Re * c.Re - Im * c.Im, Re * c.Im + c.Re * Im);
    }

    Complex operator /(const Complex& c) const
    {
        float d = c.Re * c.Re + c.Im * c.Im;
        return Complex((Re * c.Re + Im * c.Im) / d, (Im * c.Re - Re * c.Im) / d);
    }
    
    //����� ���������� ������������ �����

    Complex ComplexConjugate() const
    {
        return Complex(Re, -Im);
    }

    double doubleMod() {
        return sqrt(Re * Re + Im * Im);
    }

    double Arg() 
    {
        if (doubleMod() == 0) return 0;
        else if (Re > 0) {
            return atan(Im / Re);
        }
        else if (Re < 0) {
            if (Im >= 0)
                return acos(-1) + atan(Im / Re);
            else
                return -acos(-1) + atan(Im / Re);
        }
        else {
            if (Im > 0)
                return acos(0);
            else
                return -acos(0);
        }
    }
};

inline ostream& operator << (ostream& o, const Complex& c)
{
    return o << '(' << c.Re << ", " << c.Im << ')';
}
