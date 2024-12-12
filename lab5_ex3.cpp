#include "lab5_ex3.h"

logical_values_array::logical_values_array(unsigned int value) : _value(value) {}

unsigned int logical_values_array::getValue() const {
    return _value;
}

logical_values_array logical_values_array::inversion() {
    _value = ~_value;
    return *this;
}

logical_values_array logical_values_array::conjunction(const logical_values_array& second) {
    return logical_values_array(_value & second.getValue());
}

logical_values_array logical_values_array::conjunction(unsigned int second) {
    return logical_values_array(_value & second);
}

// x V y = -(-x /\ -y)
logical_values_array logical_values_array::disjunction(logical_values_array second) {
    return (inversion().conjunction(second.inversion())).inversion();
}

logical_values_array logical_values_array::disjunction(unsigned int second) {
    return disjunction(logical_values_array(second));
}

// x -> y = -x V y
logical_values_array logical_values_array::implication(const logical_values_array& second) {
    return inversion().disjunction(second);
}

logical_values_array logical_values_array::implication(unsigned int second) {
    return inversion().disjunction(second);
}

// -(x -> y)

logical_values_array logical_values_array::coimplication(const logical_values_array& second) {
    return implication(second).inversion();
}

logical_values_array logical_values_array::coimplication(unsigned int second) {
    return implication(second).inversion();
}

// x ~ y = (x -> y) /\ (y -> x)
logical_values_array logical_values_array::equality(logical_values_array second) {
    return implication(second).conjunction(second.implication(*this));
}

logical_values_array logical_values_array::equality(unsigned int second) {
    return equality(logical_values_array(second));
}

// x + y = -(x ~ y)
logical_values_array logical_values_array::addModul2(const logical_values_array& second) {
    return equality(second).inversion();
}

logical_values_array logical_values_array::addModul2(unsigned int second) {
    return equality(second).inversion();
}

// = -(x V y)
logical_values_array logical_values_array::peirce(const logical_values_array& second) {
    return disjunction(second).inversion();
}

logical_values_array logical_values_array::peirce(unsigned int second) {
    return disjunction(second).inversion();
}

// -(x /\ y)
logical_values_array logical_values_array::sheffer(const logical_values_array& second) {
    return conjunction(second).inversion();
}

logical_values_array logical_values_array::sheffer(unsigned int second) {
    return conjunction(second).inversion();
}

bool logical_values_array::equals(const logical_values_array& first, const logical_values_array& second) {
    return first.getValue() == second.getValue();
}

unsigned int logical_values_array::get_bit(unsigned int bit) {
    return (_value >> (bit % (sizeof(unsigned int) * 8))) & 1;
}

statuses logical_values_array::tochar(char *& mass) {
    int size = sizeof(unsigned int) * 8;
    mass = (char * ) calloc(size, sizeof(char));
    if (mass == NULL) {
        return MEMORY_TROUBLE;
    }
    for (int i = 0; i < size; i++) {
        mass[i] = get_bit(size - i - 1) + '0';
    }
    return OK;

}


int main() {
    logical_values_array a(1024);
    char * mass;
    if (a.tochar(mass) == MEMORY_TROUBLE) {
        std::cout << "memory trouble";
        return MEMORY_TROUBLE;
    }
    std::cout << mass;
    free(mass);
}