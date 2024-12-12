#include "lab5_ex1.h"

binary_int::binary_int() : number_(0) {}

binary_int::binary_int(int number) {
    number_ = number;
}

int binary_int::getNum() {
    return number_;
}

binary_int binary_int::operator-()& {
    number_ = ~number_;
    operator++();
    return *this;
}

binary_int& binary_int::operator++()& {
    int bit = 1;
    if (number_ == -1) {
        number_ = 0;
        return *this;
    }
    // идем по битам 1, пока не встретим 0 и нулим их, чтобы потом вместо 0 поставить 1
    // и таким образом прибавим единицу
    while ((bit & number_) > 0) {
        number_ = ~bit & number_;
        bit = bit << 1;
    }
    number_ = number_ | bit;
    return *this;

}
binary_int binary_int::operator++(int)& {
    int bit = 1;
    binary_int temp = *this;
    if (number_ == -1) {
        number_ = 0;
        return temp;
    }
    while ((bit & number_) > 0) {
        number_ = ~bit & number_;
        bit = bit << 1;
    }
    number_ = number_ | bit;
    return temp;

}

binary_int& binary_int::operator--()& {
    if (number_ == 0) {
        number_ = -1;
        return *this;
    }
    int bit = 1;
    while ((bit & number_) == 0) {
        number_ = bit | number_;
        bit = bit << 1;
    }
    number_ = ~bit & number_;
    return *this;
}

binary_int binary_int::operator--(int)& {
    int bit = 1;
    binary_int temp = *this;
    if (number_ == 0) {
        number_ = -1;
        return temp;
    }
    while ((bit & number_) == 0) {
        number_ = bit | number_;
        bit = bit << 1;
    }
    number_ = ~bit & number_;
    return temp;
}

binary_int binary_int::operator<<(const binary_int& second) {
    return binary_int(number_ << second.number_);
}

binary_int binary_int::operator<<(int second) {
    return binary_int(number_ << second);
}

binary_int binary_int::operator>>(const binary_int& second) {
    return binary_int(number_ >> second.number_);
}

binary_int binary_int::operator>>(int second) {
    return binary_int(number_ >> second);
}

binary_int& binary_int::operator<<=(const binary_int& second)& {
    *this = *this << second;
    return *this;
}

binary_int& binary_int::operator<<=(int second)& {
    *this = *this << second;
    return *this;
}

binary_int& binary_int::operator>>=(const binary_int& second)& {
    *this = *this >> second;
    return *this;
}

binary_int& binary_int::operator>>=(int second)& {
    *this = *this >> second;
    return *this;
}

bool binary_int::operator>=(const binary_int& second) {
    return number_ >= second.number_;
}

bool binary_int::operator>=(int second) {
    return number_ >= second;
}

bool binary_int::operator==(const binary_int& second) {
    return number_ == second.number_;
}

bool binary_int::operator==(int second) {
    return number_ == second;
}

bool binary_int::operator<=(int second) {
    return number_ <= second;
}

bool binary_int::operator>(const binary_int& second) {
    return number_ > second.number_;
}

bool binary_int::operator>(int second) {
    return number_ > second;
}

binary_int binary_int::operator&(const binary_int& second) {
    return binary_int(number_ & second.number_);
}

binary_int binary_int::operator&(int second) {
    return binary_int(number_ & second);
}

std::ostream& operator<<(std::ostream &os, binary_int number) {
    binary_int size = binary_int(sizeof(int) * 8);
    int zeroflag = 0;
    for (binary_int i = --size; i >= 0; i--) {
        if (zeroflag == 1) {
            os << ((number.getNum() >> i.getNum()) & 1);
        }
        else if (((number.getNum() >> i.getNum()) & 1) != 0 && zeroflag == 0) {
            zeroflag = 1;
            os << ((number.getNum() >> i.getNum()) & 1);
        }
    }
    if (zeroflag == 0) {
        os << 0;
    }
    return os;
}

binary_int binary_int::operator+(const binary_int& second) const {
    int a = number_;
    int b = second.number_;
    int peren;
    while (b != 0) {
        // вычисляем места, где на битах будет обе 1 и получившуюся сумму переносим влево 
        peren = (a & b) << 1;
        // складываем, но не переносим  
        a = a ^ b;
        // следующую итерацию будем складывать с полученным "переносом"                
        b = peren;   
    }
    return binary_int(a);
}

binary_int binary_int::operator+(int second) const{
    int a = number_;
    int b = second;
    int peren;
    while (b != 0) {
        peren = (a & b) << 1;
        a = a ^ b;              
        b = peren;   
    }
    return binary_int(a);
}

binary_int& binary_int::operator+=(const binary_int& second)& {
    int b = second.number_;
    int peren;
    while (b != 0) {
        peren = (number_ & b) << 1;
        number_ = number_ ^ b;               
        b = peren;   
    }
    return *this;
}

binary_int& binary_int::operator+=(int second)& {
    int peren;
    while (second != 0) {
        peren = (number_ & second) << 1; 
        number_ = number_ ^ second;            
        second = peren;   
    }
    return *this;
}

binary_int binary_int::operator-(binary_int second) {
    return -second + *this;
}

binary_int binary_int::operator-(int second) {
    return *this + (-second);
}

binary_int& binary_int::operator-=(const binary_int& second)& {
    *this = *this - second;
    return *this;
}

binary_int& binary_int::operator-=(int second)& {
    *this = *this - second;
    return *this;
}

binary_int binary_int::operator*(binary_int second) {
    binary_int result(0);
    int flag = 0;
    if (second <= 0) {
        flag = 1;
        second = -second;
    }
    for (;second >= 1; second--) {
        result += *this;
    }
    if (flag) {
        result = -result;
    }
    return result;
}

binary_int binary_int::operator*(int second) {
    return *this * binary_int(second);
}

binary_int& binary_int::operator*=(binary_int second)& {
   *this = *this * second;
   return *this;
}

binary_int& binary_int::operator*=(int second)& {
   *this = *this * second;
   return *this;
}

std::pair <binary_int, binary_int> binary_int::func() {
    binary_int count(0);
    binary_int current_num(1);
    binary_int count_mask(0);
    int mask1 = 0;
    int mask2 = 0;
    int bit = 1;
    int flag = 0;
    while (current_num <= number_) {
        current_num *= 2;
        count++;
        if (flag == 0) {
            flag = 1;
            count_mask++;
        }
        else {
            flag = 0;
        }
    }
    if (count == number_ * 2) {
        count--;
        count_mask--;
    }
    for (; count > 0; count--) {
        if (count > count_mask) {
            mask1 = mask1 | bit;
        }
        else {
            mask2 = mask2 | bit;
        }
        bit = bit << 1;
    }
    return {binary_int(mask2 & number_), binary_int(mask1 & number_)};
    
}




int main() {
    binary_int a(1024);
    binary_int b(17);
    std::cout << b << "\n";
    std::pair<binary_int, binary_int> ans = a.func();
    std::cout << ans.first << "\n" << ans.second << "\n";
    std::cout << b + 2;
    
} 
