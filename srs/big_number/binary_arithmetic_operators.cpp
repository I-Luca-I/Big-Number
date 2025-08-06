#include "../../include/big_number.h"

big_number big_number::operator+(big_number other) {
    std::pair<big_number, big_number> terms = {*this, other};
    big_number sum;
    big_number::equalize_sizes(terms.first, terms.second);

    terms.first.data.push_front(0);
    terms.first.data.push_front(0);
    terms.first.integer_part_size += 2;
    terms.second.data.push_front(0);
    terms.second.data.push_front(0);
    terms.second.integer_part_size += 2;

    sum.integer_part_size = terms.first.integer_part_size;
    sum.fractional_part_size = terms.first.fractional_part_size;
    if (terms.first.negative and terms.second.negative) {
        sum.negative = true;
        terms.first.negative = false;
        terms.second.negative = false;
    }

    // Setup ones' complement
    bool carry = terms.first.negative or terms.second.negative;
    if (terms.first.negative) terms.first = ~terms.first;
    if (terms.second.negative) terms.second = ~terms.second;

    for (int i=terms.first.size()-1; i>=0; i--) {
        sum.data.push_front(terms.first.data.get(i) xor terms.second.data.get(i) xor carry);
        carry = (terms.first.data.get(i) and terms.second.data.get(i)) or (terms.first.data.get(i) and carry) or (terms.second.data.get(i) and carry);
    }

    if (sum.data.get(0)) {
        sum = ~sum;
        carry = true;
        for (int i=sum.size()-1; i>=0; i--) {
            int res = sum.data.get(i) xor carry;
            carry = (sum.data.get(i) and carry);
            sum.data.set(i, res);
        }
        sum.negative = true;
    }

    return sum;
}

big_number big_number::operator-(big_number other) {
    return *this + (-other);
}
