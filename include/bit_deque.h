#pragma once
#include <deque>
#include <string>

#define DATA_SIZE 8

class bit_deque {
private:
    std::deque<char> data;
    int spare_bits_back;
    int spare_bits_front;
public:
    bit_deque(std::string bits="0");
    int size();
    bool get(int index);
    void set(int index, bool value);
    void push_back(bool value);
    void push_front(bool value);
    void pop_back();
    void pop_front();
    std::string to_string();
};
