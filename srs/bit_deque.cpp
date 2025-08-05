#include <stdexcept>
#include "../include/bit_deque.h"

// Complexity: Linear in bits.length()
bit_deque::bit_deque(std::string bits) {
    spare_bits_back = 1;
    spare_bits_front = DATA_SIZE-1;
    data.push_back(0);
    for (int i=0; i<bits.length(); i++) {
        if (bits[i] != '0' and bits[i] != '1') throw std::invalid_argument("the argument \"" + bits + "\" is malformed (contains non 1s or 0s)");
        push_back(bits[i]-'0');
    }
}

// Complexity: Constant
int bit_deque::size() { 
    return (data.size() * DATA_SIZE) - spare_bits_back - spare_bits_front;
}

// Complexity: Constant
bool bit_deque::get(int index) {
    if (index >= size() or index < 0) throw std::out_of_range("index " + std::to_string(index) + " is out of bounds for deque of size " + std::to_string(size()));
    
    index += spare_bits_front;
    int byte_index = index/DATA_SIZE;
    int bit_index = index - (byte_index*DATA_SIZE);
    return (data[byte_index] >> (DATA_SIZE-bit_index-1)) & 0b00000001;
}

// Complexity: Constant
void bit_deque::set(int index, bool value) {
    if (index >= size() or index < 0) throw std::out_of_range("index " + std::to_string(index) + " is out of bounds for deque of size " + std::to_string(size()));

    index += spare_bits_front;
    int byte_index = index/DATA_SIZE;
    int bit_index = index - (byte_index*DATA_SIZE);
    if (value) data[byte_index] |= value << (DATA_SIZE-bit_index-1);
    else data[byte_index] &= ~(!value << (DATA_SIZE-bit_index-1));
}

// Complexity: Constant
void bit_deque::push_back(bool value) {
    if (spare_bits_back == 0) {
        data.push_back(0);
        spare_bits_back = DATA_SIZE-1;
    } else {
        spare_bits_back--;
    }

    set(size()-1, value);
}

// Complexity: Constant
void bit_deque::push_front(bool value) {
    if (spare_bits_front == 0) {
        data.push_front(0);
        spare_bits_front = DATA_SIZE-1;
    } else {
        spare_bits_front--;
    }

    set(0, value);
}

// Complexity: Constant
void bit_deque::pop_back() {
    if (size() == 0) throw std::out_of_range("can't pop from deque of size 0");

    if (spare_bits_back == DATA_SIZE-1) {
        data.pop_back();
        spare_bits_back = 0;
    } else {
        spare_bits_back++;
    }
}

// Complexity: Constant
void bit_deque::pop_front() {
    if (size() == 0) throw std::out_of_range("can't pop from deque of size 0");

    if (spare_bits_front == DATA_SIZE-1) {
        data.pop_front();
        spare_bits_front = 0;
    } else {
        spare_bits_front++;
    }
}

// Complexity: Linear in size()
std::string bit_deque::to_string() {
    std::string r = "";
    for (int i=0; i<size(); i++) {
        r += get(i)+'0';
    }
    return r;
}
