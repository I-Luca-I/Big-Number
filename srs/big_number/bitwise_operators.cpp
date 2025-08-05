#include <stdexcept>
#include "../../include/big_number.h"

// Complexity: Linear in size()
big_number big_number::operator&(big_number other) {
    big_number::equalize_sizes(*this, other);
    big_number b;
    b.integer_part_size = this->integer_part_size;
    b.fractional_part_size = this->fractional_part_size;
    b.negative = this->negative and other.negative;
    for (int i=0; i<this->size(); i++) {
        b.data.push_back(this->data.get(i) and other.data.get(i));
    }
    return b;
}

// Complexity: Linear in size()
big_number big_number::operator|(big_number other) {
    big_number::equalize_sizes(*this, other);
    big_number b;
    b.integer_part_size = this->integer_part_size;
    b.fractional_part_size = this->fractional_part_size;
    b.negative = this->negative or other.negative;
    for (int i=0; i<this->size(); i++) {
        b.data.push_back(this->data.get(i) or other.data.get(i));
    }
    return b;
}

// Complexity: Linear in size()
big_number big_number::operator^(big_number other) {
    big_number::equalize_sizes(*this, other);
    big_number b;
    b.integer_part_size = this->integer_part_size;
    b.fractional_part_size = this->fractional_part_size;
    b.negative = this->negative xor other.negative;
    for (int i=0; i<this->size(); i++) {
        b.data.push_back(this->data.get(i) xor other.data.get(i));
    }
    return b;
}

// Complexity: Linear in size()
big_number big_number::operator~() {
    big_number b;
    b.integer_part_size = this->integer_part_size;
    b.fractional_part_size = this->fractional_part_size;
    b.negative = !this->negative;
    for (int i=0; i<this->size(); i++) {
        b.data.push_back(!this->data.get(i));
    }
    return b;
}

// Complexity: Linear in size()
big_number big_number::operator<<(int shift_count) {
    if (shift_count < 0) throw std::out_of_range("left shift count is negative");

    big_number b = *this;
    b.integer_part_size += shift_count;

    for (int i=0; i<shift_count; i++) {
        b.data.push_front(0);
    }

    for (int i=0; i<b.size()-shift_count; i++) {
        b.data.set(i, b.data.get(i+shift_count));
    }

    for (int i=b.size()-shift_count; i<b.size(); i++) {
        b.data.set(i, 0);
    }
    return b;
}

// Complexity: Linear in size()
big_number big_number::operator>>(int shift_count) {
    if (shift_count < 0) throw std::out_of_range("right shift count is negative");

    big_number b = *this;
    b.fractional_part_size += shift_count;

    for (int i=0; i<shift_count; i++) {
        b.data.push_back(0);
    }

    for (int i=b.size()-1; i>=shift_count; i--) {
        b.data.set(i, b.data.get(i-shift_count));
    }

    for (int i=shift_count-1; i>=0; i--) {
        b.data.set(i, 0);
    }
    return b;
}
