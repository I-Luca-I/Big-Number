#include "../../include/big_number.h"

// Complexity: Linear in size()
bool big_number::operator>(big_number other) {
    if (*this == other) return false;
    if (this->negative != other.negative) return other.negative;

    big_number::equalize_sizes(*this, other);
    for (int i=0; i<this->size(); i++) {
        if (this->data.get(i) != other.data.get(i)) return (this->negative) ? !this->data.get(i) : this->data.get(i);
    }
    return false;
}

// Complexity: Linear in size()
bool big_number::operator<(big_number other) {
    return other > *this;
}

// Complexity: Linear in size()
bool big_number::operator==(big_number other) {
    this->shrink_to_fit();
    other.shrink_to_fit();
    big_number::equalize_sizes(*this, other);

    if (this->data.get(0) == 0 and this->size() == 1 and other.data.get(0) == 0 and other.size() == 1) return true;
    if (this->negative != other.negative) return false;

    for (int i=0; i<this->size(); i++) {
        if (this->data.get(i) != other.data.get(i)) return false;
    }
    return true;
}

// Complexity: Linear in size()
bool big_number::operator!=(big_number other) {
    return !(*this == other);
}

// Complexity: Linear in size()
bool big_number::operator>=(big_number other) {
    return *this > other or *this == other;
}

// Complexity: Linear in size()
bool big_number::operator<=(big_number other) {
    return *this < other or *this == other;
}
