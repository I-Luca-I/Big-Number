#include "../../include/big_number.h"

// Complexity: Constant
big_number big_number::operator+() {
    return *this;
}

// Complexity: Constant
big_number big_number::operator-() {
    big_number b = *this;
    b.negative = !b.negative;
    return b;
}

// Complexity: Linear in size()
big_number& big_number::operator++() {
    *this += big_number::binary("1");
    return *this;
}

// Complexity: Linear in size()
big_number& big_number::operator--() {
    *this -= big_number::binary("1");
    return *this;
}

// Complexity: Linear in size()
big_number big_number::operator++(int) {
    big_number b = *this;
    *this += big_number::binary("1");
    return b;
}

// Complexity: Linear in size()
big_number big_number::operator--(int) {
    big_number b = *this;
    *this -= big_number::binary("1");
    return b;
}
