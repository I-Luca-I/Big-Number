#include "../../include/big_number.h"

// Complexity: Linear in max(this->size(), other.size())
big_number& big_number::operator+=(big_number other) {
    *this = *this + other;
    return *this;
}

// Complexity: Linear in max(this->size(), other.size())
big_number& big_number::operator-=(big_number other) {
    *this = *this - other;
    return *this;
}

// Complexity: Exponential in this->size() + other.size()
big_number& big_number::operator*=(big_number other) {
    *this = *this * other;
    return *this;
}

// Complexity: Exponential in quotient.size()
big_number& big_number::operator/=(big_number other) {
    *this = *this / other;
    return *this;
}

// Complexity: Exponential in quotient.size() + divisor.size()
big_number& big_number::operator%=(big_number other) {
    *this = *this % other;
    return *this;
}
