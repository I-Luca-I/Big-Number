#pragma once
#include "bit_deque.h"

class big_number {
private:
    bit_deque data;
    bool negative;
    int integer_part_size;
    int fractional_part_size;
    
    big_number();
public:
    static big_number decimal(std::string);
    static big_number binary(std::string);
    std::string to_decimal_string();
    std::string to_binary_string();

    // Assignment
    // big_number operator=(big_number other);

    // Binary Arithmetic
    big_number operator+(big_number other);
    big_number operator-(big_number other);

    // Relational
    bool operator>(big_number other);
    bool operator<(big_number other);
    bool operator==(big_number other);
    bool operator!=(big_number other);
    bool operator>=(big_number other);
    bool operator<=(big_number other);
};
