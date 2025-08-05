#include <stdexcept>
#include "../../include/big_number.h"

big_number::big_number() {
    this->data = bit_deque();
    this->integer_part_size = 0;
    this->fractional_part_size = 0;
    this->negative = false;
}

// big_number big_number::decimal(std::string number) {}

// Complexity: Linear in number.length()
big_number big_number::binary(std::string number) {
    big_number b;
    bool fraction = false;

    for (int i=0; i<number.length(); i++) {
        if (!(number[i] == '0' or number[i] == '1' or (number[i] == '-' and i==0) or (number[i] == '.' and !fraction))) 
            throw std::logic_error("The binary number \"" + number + "\" is malformed");

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
void big_number::resize_integer(int new_size) {
    if (new_size < 0) throw std::invalid_argument("new_size can't be < 0");
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
void big_number::resize_fraction(int new_size) {
    if (new_size < 0) throw std::invalid_argument("new_size can't be < 0");
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

// std::string big_number::to_decimal_string() {}

// Complexity: Linear in this.size()
std::string big_number::to_binary_string() {
    std::string s;
    s = (this->negative) ? "-" : "";

    for (int i=0; i<this->size(); i++) {
        if (i == this->integer_part_size and this->fractional_part_size > 0) s += '.';
        s += this->data.get(i) + '0';
    }
    return s;
}
