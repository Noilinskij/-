#include <math.h>
#include <iostream>

class Complex {
    public:
        void print();
        Complex(double, double);
        Complex addition(const Complex&);
        Complex subtraction(const Complex&);
        Complex multiplication(const Complex&);
        Complex division(const Complex&);
        double modul();
        double argument();
    private:
        double real_ = 0;
        double imaginary_ = 0;
};