#include "lab5_ex6.h"

vector::vector(size_t count, double elem) {
    if (count == 0) {
        size_ = 0;
        capacity_ = 0;
    }
    else {
        reserve(count);
        for (int i = 0; i < count; i++) {
            mass_[i] = elem;
        }
        size_ = count;
        capacity_ = count;
    }
}

vector::vector(size_t count) : vector(count, 0.0) {}

vector::vector(const iterator& first, const iterator& second) {
    if (first > second) {
        reserve(first - second);
        size_ = first - second;
        for (size_t i = 0; i < first - second; i++) {
            mass_[i] = first[i];
        }
    }
    else {
        reserve(second - first);
        size_ = second - first;
        for (size_t i = 0; i < second - first; i++) {
            mass_[i] = first[i];
        }
    }
}

vector::vector(std::initializer_list<double> initl) {
    reserve(initl.size());
    size_ = initl.size();
    for (std::initializer_list<double>::iterator i = initl.begin(); i != initl.end(); i++) {
        mass_[i - initl.begin()] = *i;
    }
}

double& vector::at(size_t i) const{
        if (i >= size_) {
            throw std::out_of_range("incorrect index");
        }
        return mass_[i];
}

double& vector::front() const {
    if (!empty()) {
        return mass_[0];
    }
    throw std::logic_error("mass is empty");
}

double& vector::back() const {
    if (!empty()) {
        return mass_[size_ - 1];
    }
    throw std::logic_error("mass is empty");
}

double* vector::data() const {
    return mass_;
}

bool vector::empty() const {
    return size_ == 0;
}

int vector::size() const {
    return size_;
}

void vector::reserve(size_t num) {
    if (num > capacity_) {
        double* tmp = new double[num];
        for (size_t i = 0; i < size_; i++) {
            tmp[i] = mass_[i];
        }
        if (capacity_ != 0) {
            delete[] mass_;
        }
        mass_ = tmp;
        capacity_ = num;
    }
}

int vector::capacity() const{
    return capacity_;
}

void vector::shrink_to_fit() {
    if (capacity_ != size_) {
        double* tmp = new double[size_];
        for (size_t i = 0; i < size_; i++) {
            tmp[i] = mass_[i];
        }
        delete[] mass_;
        mass_ = tmp;
        capacity_ = size_;
    }
}

void vector::clear() {
    delete[] mass_;
    capacity_ = 0;
    size_ = 0;
}

void vector::insert(size_t index, double elem) {
    if (index > size_) {
        throw std::out_of_range("incorrect index");
    }
    if (size_ == capacity_) {
        reserve(size_ * 2 + 1);
    }
    for (size_t i = size_; i > index; i--) {
        mass_[i] = mass_[i - 1];
    }
    mass_[index] = elem;
    size_++;
}

void vector::erase(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("incorrect index");
    }
    size_--;
    for (size_t i = index; i < size_; i++) {
        mass_[i] = mass_[i + 1];
    }

}

void vector::push_back(double elem) {
    if (size_ == capacity_) {
        reserve(size_ * 2 + 1);
    }
    mass_[size_] = elem;
    size_++;
}

void vector::pop_back(double elem) {
    if (size_ == 0) {
        throw std::out_of_range("vector is empty");
    }
    size_--;
}

void vector::resize(size_t num, double elem) {
    if (num > size_) {
        reserve(num);
    }
    for (int i = size_; i < num; i++) {
        mass_[i] = elem;
    }
    size_ = num;
}

std::partial_ordering vector::operator<=>(const vector& second) const {
    double eps = 0.01;
    size_t min_size = size_;
    if (size_ > second.size()) {
        min_size = second.size();
    }
    double * data = second.data();
    for (size_t i = 0; i < min_size; i++) {
        if (isnan(mass_[i]) || isnan(data[i])) {
            return std::partial_ordering::unordered;
        }
        if (mass_[i] - data[i] > eps) {
            return std::partial_ordering::greater;
        }
        else if (data[i] - mass_[i] > eps) {
            return std::partial_ordering::less;
        }
    }
    if (size_ > second.size()) {
        return std::partial_ordering::greater;
    }
    else if (size_ < second.size()) {
        return std::partial_ordering::less;
    }
    return std::partial_ordering::equivalent;
}

bool vector::operator==(const vector& second) const{
    double eps = 0.01;
    if (size_ != second.size()) {
        return false;
    }
    double * data = second.data();
    for (size_t i = 0; i < size_; i++) {
        if (fabs(mass_[i] - data[i]) > eps) {
            return false;
        }
    }
    return true;
}

double& vector::operator[](size_t num) {
    return mass_[num];
}

double vector::operator[](size_t num) const {
    return mass_[num];
}

vector::iterator::iterator(double* ptr): iter(ptr) {}

double* vector::iterator::getPtr() const {
    return iter;
}

vector::iterator& vector::iterator::operator++()& {
    iter++;
    return *this;
}

vector::iterator vector::iterator::operator++(int) {
    iter++;
    return *this;
}

vector::iterator& vector::iterator::operator--()& {
    iter--;
    return *this;
}

vector::iterator vector::iterator::operator--(int) {
    iter--;
    return *this;
}

vector::iterator vector::iterator::operator+(size_t num) const {
    // ptr арифметика (к iter прибавится num * sizeof(double) само из-за перегрузки для double*)
    return vector::iterator(iter + num);
}

vector::iterator& vector::iterator::operator+=(size_t num)& {
    iter += num;
    return *this;
}

// тут возвращается смещенный итератор
vector::iterator vector::iterator::operator-(size_t num) const { 
    return vector::iterator(iter - num);
}

// тут возвращается кол-во элементов между итераторами
ptrdiff_t vector::iterator::operator-(const iterator& second) const {
    return iter - second.getPtr();
}

vector::iterator& vector::iterator::operator-=(size_t num)& {
    iter -= num;
    return *this;
}

bool vector::iterator::operator==(const iterator& second) const {
    return iter == second.getPtr();
}

std::strong_ordering vector::iterator::operator<=>(const iterator& second) const {
    return iter <=> second.getPtr();
}

double& vector::iterator::operator[](size_t num) const {
    return *(iter + num);
}

double& vector::iterator::operator*() const {
    return *iter;
}

double* vector::iterator::operator->() const {
    return iter;
}

vector::iterator vector::begin() {
    return iterator(mass_);
}

vector::iterator vector::end() {
    return iterator(mass_ + size_);
}

double vector::const_iterator::operator[](size_t num) const {
    return *(iter + num);
}

double vector::const_iterator::operator*() const {
    return *iter;
}

vector::const_iterator vector::cbegin() const {
    return const_iterator(mass_);
}

vector::const_iterator vector::cend() const {
    return const_iterator(mass_ + size_);
}



