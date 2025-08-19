#include <stdexcept>
#include <cmath>
#include "../../include/big_number.h"
#define LB_10 3.321928

// Complexity: Constant
big_number::big_number() {
    this->data = bit_deque();
    this->integer_part_size = 0;
    this->fractional_part_size = 0;
    this->negative = false;
    this->set_decimal_significand_precision(10);
}

// Complexity: Exponensial in number.length()
// A slight loss of precision can be expected
big_number big_number::decimal(std::string number, int significand_precision) {
    std::string to_binary[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001"};
    big_number b = big_number::binary("0");

    bool negative = false;
    bool fraction = false;
    int decimal_integer_part_size = 0;
    int decimal_fractional_part_size = 0;

    if (number[0] == '-') {
        number.erase(0, 1);
        negative = true;
    }

    for (int i=0; i<number.length(); i++) {
        if (!((number[i] >= '0' and number[i] <= '9') or (number[i] == '.' and !fraction))) throw std::invalid_argument("the decimal number \"" + number + "\" is malformed");
        
        if (number[i] == '.') fraction = true;
        else if (fraction) decimal_fractional_part_size++;
        else decimal_integer_part_size++;
    }

    // Translate integer part
    big_number magnitude = big_number::binary("1");
    for (int i=decimal_integer_part_size-1; i>=0; i--) {
        big_number value = big_number::binary(to_binary[number[i]-'0']);
        b += value * magnitude;
        magnitude *= big_number::binary("1010");
    }

    // Translate fractional part
    magnitude = big_number::binary("1");
    big_number fractional_part = big_number::binary("0");
    for (int i=number.length()-1; i>decimal_integer_part_size; i--) {
        big_number value = big_number::binary(to_binary[number[i]-'0']);
        fractional_part += value * magnitude;
        magnitude *= big_number::binary("1010");
    }
    fractional_part.set_binary_significand_precision(significand_precision);
    magnitude.set_binary_significand_precision(significand_precision);
    b.set_binary_significand_precision(significand_precision);
    b += fractional_part / magnitude;
    b.negative = negative;

    return b;
}

// Complexity: Linear in number.length()
big_number big_number::binary(std::string number) {
    big_number b;
    bool fraction = false;

    for (int i=0; i<number.length(); i++) {
        if (!(number[i] == '0' or number[i] == '1' or (number[i] == '-' and i==0) or (number[i] == '.' and !fraction))) 
            throw std::invalid_argument("the binary number \"" + number + "\" is malformed");

        if (number[i] == '-') b.negative = true;
        else if (number[i] == '.') fraction = true;
        else {
            b.data.push_back(number[i]-'0');
            if (fraction) b.fractional_part_size++;
            else b.integer_part_size++;
        }
    }
    return b;
}

// Complexity: Constant
int big_number::size() {
    return this->data.size(); // this->fractional_part_size + this->integer_part_size
}

// Complexity: Linear in abs(new_size - this->integer_part_size)
void big_number::resize_integer(unsigned int new_size) {
    while(this->integer_part_size < new_size) {
        this->data.push_front(0);
        this->integer_part_size++;
    }

    while(this->integer_part_size > new_size and this->data.get(0) == 0) {
        this->data.pop_front();
        this->integer_part_size--;
    }
}

// Complexity: Linear in abs(new_size - this->fractional_part_size)
void big_number::resize_fraction(unsigned int new_size) {
    while(this->fractional_part_size < new_size) {
        this->data.push_back(0);
        this->fractional_part_size++;
    }
    
    while(this->fractional_part_size > new_size) {
        this->data.pop_back();
        this->fractional_part_size--;
    }
}

// Complexity: Linear in this.size()
void big_number::shrink_to_fit() {
    while(this->data.get(0) == 0 and this->integer_part_size > 1) {
        this->data.pop_front();
        this->integer_part_size--;
    }

    while(this->data.get(this->size()-1) == 0 and this->fractional_part_size > 0) {
        this->data.pop_back();
        this->fractional_part_size--;
    }
}

// Complexity: Linear in abs(number_1.integer_part_size - number_2.integer_part_size) + abs(number_1.fractional_part_size - number_2.fractional_part_size)
void big_number::equalize_sizes(big_number& number_1, big_number& number_2) {
    number_1.resize_integer(std::max(number_1.integer_part_size, number_2.integer_part_size));
    number_2.resize_integer(std::max(number_1.integer_part_size, number_2.integer_part_size));
    number_1.resize_fraction(std::max(number_1.fractional_part_size, number_2.fractional_part_size));
    number_2.resize_fraction(std::max(number_1.fractional_part_size, number_2.fractional_part_size));
}

// Complexity: Constant
unsigned int big_number::get_decimal_significand_precision() {
    return this->decimal_significand_precision;
}

// Complexity: Constant
unsigned int big_number::get_binary_significand_precision() {
    return this->binary_significand_precision;
}

// Complexity: Constant
void big_number::set_decimal_significand_precision(unsigned int digits) {
    this->decimal_significand_precision = digits;
    this->binary_significand_precision = std::ceil(digits*LB_10);
}

// Complexity: Constant
void big_number::set_binary_significand_precision(unsigned int digits) {
    this->decimal_significand_precision = std::ceil(digits/LB_10);
    this->binary_significand_precision = digits;
}

// Complexity: Exponensial in this->length()
std::string big_number::to_decimal_string() {
    big_number b = *this;

    std::string s;
    s = (this->negative) ? "-" : "";

    big_number integer_part = *this;
    big_number fractional_part = *this;

    while (integer_part.fractional_part_size > 0) {
        integer_part.data.pop_back();
        integer_part.fractional_part_size--;
    }

    while (fractional_part.integer_part_size > 0) {
        fractional_part.data.pop_front();
        fractional_part.integer_part_size--;
    }
    fractional_part.data.push_front(0);
    fractional_part.integer_part_size++;

    // Translate integer part
    std::string integer_string = "";
    integer_part.set_binary_significand_precision(0);
    while (integer_part != big_number::binary("0")) {
        std::string binary_remainder = (integer_part % big_number::binary("1010")).to_binary_string();
        int decimal_remainder = 0;

        for (int i=binary_remainder.length()-1; i>=0; i--) {
            if (binary_remainder[i] == '-') continue;
            decimal_remainder += (binary_remainder[i]-'0') << (binary_remainder.length() - 1 - i);
        }
        
        integer_string += decimal_remainder + '0';
        integer_part /= big_number::binary("1010");
    }
    if (integer_string.empty()) integer_string += '0';

    for (int i=integer_string.length()-1; i>=0; i--) {
        s += integer_string[i];
    }

    if (fractional_part != big_number::binary("0")) s += '.';

    // Translate fractional part
    while (fractional_part != big_number::binary("0")) {
        fractional_part *= big_number::binary("1010");

        std::string binary_remainder = fractional_part.to_binary_string();
        if (binary_remainder[0] == '-') binary_remainder.erase(0, 1);
        int decimal_remainder = 0;

        for (int i=fractional_part.integer_part_size-1; i>=0; i--) {
            decimal_remainder += (binary_remainder[i]-'0') << (fractional_part.integer_part_size - 1 - i);
        }

        while (fractional_part.integer_part_size > 0) {
            fractional_part.data.pop_front();
            fractional_part.integer_part_size--;
        }
        fractional_part.data.push_front(0);
        fractional_part.integer_part_size++;
        
        s += decimal_remainder + '0';
    }

    return s;
}

// Complexity: Linear in this.size()
std::string big_number::to_binary_string() {
    std::string s;
    s = (this->negative) ? "-" : "";

    for (int i=0; i<this->size(); i++) {
        if ((int)(i - this->integer_part_size) >= (int)this->get_binary_significand_precision()) break;
        if (i == this->integer_part_size and this->fractional_part_size > 0) s += '.';
        s += this->data.get(i) + '0';
    }
    return s;
}
