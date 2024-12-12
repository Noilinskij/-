#include <iostream>

typedef enum statuses {
    OK,
    MEMORY_TROUBLE,
    INCORRECT_ARGUMENTS
} statuses;


class logical_values_array {
public:
    unsigned int getValue() const;
    logical_values_array(unsigned int);
    logical_values_array inversion();
    logical_values_array conjunction(const logical_values_array&);
    logical_values_array conjunction(unsigned int);
    logical_values_array disjunction(logical_values_array);
    logical_values_array disjunction(unsigned int);
    logical_values_array implication(const logical_values_array&);
    logical_values_array implication(unsigned int);
    logical_values_array coimplication(const logical_values_array&);
    logical_values_array coimplication(unsigned int);
    logical_values_array equality(logical_values_array);
    logical_values_array equality(unsigned int);
    logical_values_array addModul2(const logical_values_array&);
    logical_values_array addModul2(unsigned int);
    logical_values_array peirce(const logical_values_array&);
    logical_values_array peirce(unsigned int);
    logical_values_array sheffer(const logical_values_array&);
    logical_values_array sheffer(unsigned int);
    static bool equals(const logical_values_array&, const logical_values_array&);
    unsigned int get_bit(unsigned int);
    statuses tochar(char *&);

private:
    unsigned int _value = 0;
};