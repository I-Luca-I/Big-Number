#include "../../include/big_number.h"

// Complexity: Linear in max(this->size(), other.size())
bool big_number::operator>(big_number other) {
    std::pair<big_number, big_number> terms = {*this, other};
    if (terms.first == terms.second) return false;
    if (terms.first.negative != terms.second.negative) return terms.second.negative;

    big_number::equalize_sizes(terms.first, terms.second);
    for (int i=0; i<terms.first.size(); i++) {
        if (terms.first.data.get(i) != terms.second.data.get(i)) return (terms.first.negative) ? !terms.first.data.get(i) : terms.first.data.get(i);
    }
    return false;
}

// Complexity: Linear in max(this->size(), other.size())
bool big_number::operator<(big_number other) {
    return other > *this;
}

// Complexity: Linear in max(this->size(), other.size())
bool big_number::operator==(big_number other) {
    std::pair<big_number, big_number> terms = {*this, other};
    terms.first.shrink_to_fit();
    terms.second.shrink_to_fit();
    big_number::equalize_sizes(terms.first, terms.second);

    if (terms.first.data.get(0) == 0 and terms.first.size() == 1 and terms.second.data.get(0) == 0 and terms.second.size() == 1) return true;
    if (terms.first.negative != terms.second.negative) return false;

    for (int i=0; i<terms.first.size(); i++) {
        if (terms.first.data.get(i) != terms.second.data.get(i)) return false;
    }
    return true;
}

// Complexity: Linear in max(this->size(), other.size())
bool big_number::operator!=(big_number other) {
    return !(*this == other);
}

// Complexity: Linear in max(this->size(), other.size())
bool big_number::operator>=(big_number other) {
    return *this > other or *this == other;
}

// Complexity: Linear in max(this->size(), other.size())
bool big_number::operator<=(big_number other) {
    return *this < other or *this == other;
}
