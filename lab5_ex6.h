#include <iostream>
#include <compare>
#include <math.h>

class vector {
private:
    double* mass_;
    size_t size_ = 0;
    size_t capacity_ = 0;
public:
class iterator {
    public:
        using difference_type = ptrdiff_t;
        using value_type = double;
        using pointer = double*;
        using reference = double&;
        using iterator_category = std::random_access_iterator_tag;
        iterator(double*);
        double* getPtr() const;
        iterator& operator++()&;
        iterator operator++(int);
        iterator& operator--()&;
        iterator operator--(int);
        iterator operator+(size_t num) const;
        iterator& operator+=(size_t num)&;
        iterator operator-(size_t num) const;
        ptrdiff_t operator-(const iterator&) const;
        iterator& operator-=(size_t num)&;
        bool operator==(const iterator&) const;
        std::strong_ordering operator<=>(const iterator&) const;
        double& operator[] (size_t num) const;
        double& operator*() const;
        double* operator->() const;
    protected:
        double* iter;
    };

    class const_iterator : public iterator {
    public:
        double operator[] (size_t num) const;
        double operator*() const;

    };
    vector(size_t, double);
    vector(size_t);
    vector(const iterator&, const iterator&);
    vector(std::initializer_list<double>);
    double& at(size_t) const;
    double& front() const;
    double& back() const;
    double * data() const;
    bool empty() const;
    int size() const;
    void reserve(size_t);
    int capacity() const;
    void shrink_to_fit();
    void clear();
    void insert(size_t, double);
    void erase(size_t);
    void push_back(double);
    void pop_back(double);
    void resize(size_t, double);
    std::partial_ordering operator<=>(const vector&) const;
    bool operator==(const vector&) const;
    double& operator[] (size_t num);
    double operator[] (size_t num) const;
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

};