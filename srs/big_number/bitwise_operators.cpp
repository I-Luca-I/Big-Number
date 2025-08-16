#include <stdexcept>
#include "../../include/big_number.h"

// Complexity: Linear in this->size()
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

// Complexity: Linear in this->size()
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

// Complexity: Linear in this->size()
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

// Complexity: Linear in this->size()
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

// Complexity: Linear in shift_count
big_number big_number::operator<<(unsigned int shift_count) {
    big_number b = *this;
    b.integer_part_size += shift_count;
    for (int i=0; i<shift_count; i++) {
        b.data.push_back(0);
    }
    return b;
}

// Complexity: Linear in shift_count
big_number big_number::operator>>(unsigned int shift_count) {
    big_number b = *this;
    b.fractional_part_size += shift_count;
    for (int i=0; i<shift_count; i++) {
        b.data.push_front(0);
    }
    return b;
}
