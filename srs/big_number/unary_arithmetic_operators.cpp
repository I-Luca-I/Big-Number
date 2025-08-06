#include "../../include/big_number.h"

big_number big_number::operator+() {
    return *this;
}

big_number big_number::operator-() {
    big_number b = *this;
    b.negative = !b.negative;
    return b;
}

big_number& big_number::operator++() {
    *this += big_number::binary("1");
    return *this;
}

big_number& big_number::operator--() {
    *this -= big_number::binary("1");
    return *this;
}

big_number big_number::operator++(int) {
    big_number b = *this;
    *this += big_number::binary("1");
    return b;
}

big_number big_number::operator--(int) {
    big_number b = *this;
    *this -= big_number::binary("1");
    return b;
}
