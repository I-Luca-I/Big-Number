#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "../include/bit_deque.h"

TEST_CASE("bit_deque - input and output") {
    bit_deque b;

    std::string bytes = "11111111";
    for (int i=4; i<=64; i*=4) {
        bytes = bytes + bytes + bytes + bytes;
        BENCHMARK("initialization - " + std::to_string(i) + " bytes") {
            return b = bit_deque(bytes);
        };
    }

    bytes = "11111111";
    for (int i=4; i<=64; i*=4) {
        bytes = bytes + bytes + bytes + bytes;
        b = bit_deque(bytes);
        BENCHMARK("to_string - " + std::to_string(i) + " bytes") {
            return b.to_string();
        };
    }
}

TEST_CASE("bit_deque - get and set") {
    bit_deque b = bit_deque("10011001");
    BENCHMARK("get") {
        return b.get(0);
    };

    BENCHMARK("set") {
        return b.set(0, 1);
    };
}

TEST_CASE("bit_deque - push and pop") {
    bit_deque b = bit_deque("1111111111111111111111111111111111111111111111111111111111111111");
    BENCHMARK("push front - 1 bit") {
        return b.push_front(0);
    };

    BENCHMARK("push front - 64 bits") {
        for (int i=0; i<64; i++) {
            b.push_front(0);
        }
        return;
    };
}
