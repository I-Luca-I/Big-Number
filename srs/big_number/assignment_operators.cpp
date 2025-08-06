#include "../../include/big_number.h"

big_number& big_number::operator+=(big_number other) {
    *this = *this + other;
    return *this;
}

big_number& big_number::operator-=(big_number other) {
    *this = *this - other;
    return *this;
}
