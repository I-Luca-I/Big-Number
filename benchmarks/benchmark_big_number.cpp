#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "../include/big_number.h"

TEST_CASE("big_number - input and output") {
    big_number b = big_number::binary("0");

    std::string bytes = "11111111";
    for (int i=4; i<=64; i*=4) {
        bytes = bytes + bytes + bytes + bytes;
        BENCHMARK("binary initialization - " + std::to_string(i) + " bytes") {
            return b = big_number::binary(bytes);
        };
    }

    bytes = "11111111";
    for (int i=4; i<=64; i*=4) {
        bytes = bytes + bytes + bytes + bytes;
        b = big_number::binary(bytes);
        BENCHMARK("binary to_string - " + std::to_string(i) + " bytes") {
            return b.to_binary_string();
        };
    }
}

TEST_CASE("big_number - arithmetic operators") {
    BENCHMARK("standard sum - 4 bytes") {
        return 0b11111111111111111111111111111111 + 0b11111111111111111111111111111111;
    };

    big_number b = big_number::binary("0");
    std::string bytes = "11111111";
    for (int i=4; i<=64; i*=4) {
        bytes = bytes + bytes + bytes + bytes;
        b = big_number::binary(bytes);
        BENCHMARK("sum - " + std::to_string(i) + " bytes") {
            return b + b;
        };
    }

    b = big_number::binary("0");
    bytes = "11111111";
    for (int i=4; i<=64; i*=4) {
        bytes = bytes + bytes + bytes + bytes;
        b = big_number::binary(bytes);
        BENCHMARK("multiplication - " + std::to_string(i) + " bytes") {
            return b * b;
        };
    }
}
