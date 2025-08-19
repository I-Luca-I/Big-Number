#include "../../include/big_number.h"

// Complexity: Linear in x.fractional_part_size
big_number big_number::ceil(big_number x) {
    big_number b = trunc(x);
    if (!b.negative) b++;
    return b;
}

// Complexity: Linear in x.fractional_part_size
big_number big_number::floor(big_number x) {
    big_number b = trunc(x);
    if (b.negative) b--;
    return b;
}

// Complexity: Linear in x.fractional_part_size
big_number big_number::trunc(big_number x) {
    big_number b = x;
    while (b.fractional_part_size > 0) {
        b.data.pop_back();
        b.fractional_part_size--;
    }
    return b;
}

// Complexity: Linear in x.fractional_part_size
big_number big_number::round(big_number x) {
    if (x.data.get(x.integer_part_size)) return (x.negative) ? floor(x) : ceil(x);
    else return (x.negative) ? ceil(x) : floor(x);
}
