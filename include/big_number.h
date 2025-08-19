#pragma once
#include "bit_deque.h"

class big_number {
private:
    bit_deque data;
    bool negative;
    unsigned int integer_part_size;
    unsigned int fractional_part_size;
    unsigned int decimal_significand_precision;
    unsigned int binary_significand_precision;
    
    big_number();
public:
    static big_number decimal(std::string number, int significand_precision=33);
    static big_number binary(std::string number);
    int size();
    void resize_integer(unsigned int new_size);
    void resize_fraction(unsigned int new_size);
    void shrink_to_fit();
    static void equalize_sizes(big_number& bg1, big_number& bg2);
    unsigned int get_decimal_significand_precision();
    unsigned int get_binary_significand_precision();
    void set_decimal_significand_precision(unsigned int digits);
    void set_binary_significand_precision(unsigned int digits);
    std::string to_decimal_string();
    std::string to_binary_string();

    // Assignment Operators
    big_number& operator+=(big_number other);
    big_number& operator-=(big_number other);
    big_number& operator*=(big_number other);
    big_number& operator/=(big_number other);
    big_number& operator%=(big_number other);

    // Binary Arithmetic Operators
    big_number operator+(big_number other);
    big_number operator-(big_number other);
    big_number operator*(big_number other);
    big_number operator/(big_number other);
    big_number operator%(big_number other);

    // Unary Arithmetic Operators
    big_number operator+();
    big_number operator-();
    big_number& operator++();
    big_number& operator--();
    big_number operator++(int);
    big_number operator--(int);

    // Relational Operators
    bool operator>(big_number other);
    bool operator<(big_number other);
    bool operator==(big_number other);
    bool operator!=(big_number other);
    bool operator>=(big_number other);
    bool operator<=(big_number other);

    // Bitwise Operators
    big_number operator&(big_number other);
    big_number operator|(big_number other);
    big_number operator^(big_number other);
    big_number operator~();
    big_number operator<<(unsigned int shift_count);
    big_number operator>>(unsigned int shift_count);
};
