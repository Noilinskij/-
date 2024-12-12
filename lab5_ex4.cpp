#include "lab5_ex4.h"

void Complex::print() {
    std::cout << real_ << " + i * " << imaginary_ << "\n";
}

Complex::Complex(double real, double imaginary) {
    real_ = real;
    imaginary_ = imaginary;
}

Complex Complex::addition(const Complex& second) {
    return Complex(real_ + second.real_, 
        imaginary_ + second.imaginary_);
}

Complex Complex::subtraction(const Complex& second) {
    return Complex(real_ - second.real_, 
        imaginary_ - second.imaginary_);
}

Complex Complex::multiplication(const Complex& second) {
    return Complex(real_ * second.real_ - imaginary_ * second.imaginary_,
        imaginary_ * second.real_ + second.imaginary_ * real_);
}

Complex Complex::division(const Complex& second) {
    return Complex((real_ * second.real_ + imaginary_ * second.imaginary_) 
        / (second.real_ * second.real_ + second.imaginary_ * second.imaginary_), 
        (second.real_ * imaginary_ - real_ * second.imaginary_) / 
        (second.real_ * second.real_ + second.imaginary_ * second.imaginary_));
}

double Complex::modul() {
    return sqrt(real_ * real_ + imaginary_ * imaginary_);
}

double Complex::argument() {
    return atan(imaginary_ / real_);
}



int main() {
    Complex first(1, 3);
    Complex second(1, 2);
    Complex third = first.division(second);
    third.print();
    std::cout << third.modul() << "\n";
    std::cout << third.argument() << "\n";
}
