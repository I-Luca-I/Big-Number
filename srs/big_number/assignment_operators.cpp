#include "../../include/big_number.h"

// Complexity: Linear in size()
big_number& big_number::operator+=(big_number other) {
    *this = *this + other;
    return *this;
}

// Complexity: Linear in size()
big_number& big_number::operator-=(big_number other) {
    *this = *this - other;
    return *this;
}

// Complexity: Exponential in size()
big_number& big_number::operator*=(big_number other) {
    *this = *this * other;
    return *this;
}
