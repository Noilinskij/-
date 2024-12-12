#include <iostream>
#include <limits.h>

class binary_int {
public:
    binary_int();
    binary_int(int);
    int getNum();
    binary_int operator-()&;
    binary_int& operator++()&;
    binary_int operator++(int)&;
    binary_int& operator--()&;
    binary_int operator--(int)&;
    binary_int operator<<(const binary_int&);
    binary_int operator<<(int);
    binary_int operator>>(const binary_int&);
    binary_int operator>>(int);
    binary_int& operator<<=(const binary_int&)&;
    binary_int& operator<<=(int)&;
    binary_int& operator>>=(const binary_int&)&;
    binary_int& operator>>=(int)&;
    binary_int operator&(const binary_int&);
    binary_int operator&(int);
    bool operator>=(const binary_int&);
    bool operator>=(int);
    bool operator<=(int);
    bool operator==(const binary_int&);
    bool operator==(int);
    binary_int operator+(const binary_int&) const;
    binary_int operator+(int) const;
    binary_int& operator+=(const binary_int&)&;
    binary_int& operator+=(int)&;
    binary_int operator-(binary_int);
    binary_int operator-(int);
    binary_int& operator-=(const binary_int&)&;
    binary_int& operator-=(int)&;
    binary_int operator*(binary_int);
    binary_int operator*(int);
    binary_int& operator*=(binary_int)&;
    binary_int& operator*=(int)&;
    bool operator>(const binary_int&);
    bool operator>(int);
    std::pair<binary_int, binary_int> func();

private:
    int number_;

};