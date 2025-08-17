#include <stdexcept>
#include "../../include/big_number.h"

// Complexity: Linear in max(this->size(), other.size())
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
            if (carry == 0) break;
        }
        sum.negative = true;
    }

    return sum;
}

// Complexity: Linear in max(this->size(), other.size())
big_number big_number::operator-(big_number other) {
    return *this + (-other);
}

// Complexity: Exponential in this->size() + other.size()
big_number big_number::operator*(big_number other) {
    std::pair<big_number, big_number> terms = {*this, other};
    big_number product = big_number::binary("0");

    std::pair<int, int> terms_ones = {0, 0};
    for (int i=0; i<terms.first.size(); i++) {
        terms_ones.first += terms.first.data.get(i);
    }
    for (int i=0; i<terms.second.size(); i++) {
        terms_ones.second += terms.second.data.get(i);
    }
    if (terms_ones.second > terms_ones.first) terms = {terms.second, terms.first};

    terms.first.shrink_to_fit();
    terms.second.shrink_to_fit();
    big_number::equalize_sizes(terms.first, product);

    product.negative = terms.first.negative xor terms.second.negative;
    terms.first.negative = product.negative;
    terms.second.negative = product.negative;

    for (int i=terms.second.size()-1; i>=0; i--) {
        if (terms.second.data.get(i)) product += terms.first << (terms.second.size() - 1 - i);
    }

    product.integer_part_size = product.size() - terms.first.fractional_part_size - terms.second.fractional_part_size;
    product.fractional_part_size = terms.first.fractional_part_size + terms.second.fractional_part_size;

    return product;
}

// Complexity: Exponential in quotient.size()
big_number big_number::operator/(big_number other) {
    big_number dividend = *this;
    big_number divisor = other;
    big_number quotient = big_number::binary("0");

    if (divisor == big_number::binary("0")) throw std::domain_error("can't divide by 0");

    dividend.shrink_to_fit();
    divisor.shrink_to_fit();
    big_number::equalize_sizes(dividend, divisor);

    dividend.integer_part_size += dividend.fractional_part_size;
    divisor.integer_part_size += divisor.fractional_part_size;
    dividend.fractional_part_size = 0;
    divisor.fractional_part_size = 0;

    quotient.negative = dividend.negative xor divisor.negative;
    dividend.negative = false;
    divisor.negative = false;

    quotient.set_binary_significand_precision(std::min(dividend.get_binary_significand_precision(), divisor.get_binary_significand_precision()));

    int shifts = 0;
    while (divisor.data.get(0) == 0) {
        divisor = divisor << 1;
        divisor.data.pop_front();
        divisor.integer_part_size--;
        shifts++;
    }

    while ((dividend != big_number::binary("0") or shifts >= 0) and quotient.fractional_part_size <= quotient.get_binary_significand_precision()) {
        quotient.data.push_back(divisor <= dividend);
        if (shifts >= 0) quotient.integer_part_size++;
        else quotient.fractional_part_size++;

        if (divisor <= dividend) {
            dividend -= divisor;
        }

        divisor = divisor >> 1;
        shifts--;
    }

    while (quotient.fractional_part_size > quotient.get_binary_significand_precision()) {
        quotient.data.pop_back();
        quotient.fractional_part_size--;
    }
    
    return quotient;
}

// Complexity: Exponential in quotient.size() + divisor.size()
big_number big_number::operator%(big_number other) {
    big_number dividend = *this;
    big_number divisor = other;
    big_number remainder;

    if (divisor == big_number::binary("0")) throw std::domain_error("can't modulo by 0");
    if (divisor.fractional_part_size > 0 or dividend.fractional_part_size > 0) throw std::domain_error("can't modulo decimal numbers");

    divisor.negative = dividend.negative;;

    dividend.set_binary_significand_precision(0);
    divisor.set_binary_significand_precision(0);

    // remainder = dividend - (divisor * (dividend / divisor));
    big_number a = dividend/divisor;
    big_number b = divisor * a;
    remainder = dividend - b;
    return remainder;
}
