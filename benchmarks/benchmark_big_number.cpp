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

    bytes = "9";
    for (int i=4; i<=64; i*=4) {
        bytes = bytes + bytes + bytes + bytes;
        BENCHMARK("decimal initialization - " + std::to_string(i) + " digits") {
            return b = big_number::decimal(bytes);
        };
    }

    bytes = "9";
    for (int i=4; i<=64; i*=4) {
        bytes = bytes + bytes + bytes + bytes;
        b = big_number::decimal(bytes);
        BENCHMARK("decimal to_string - " + std::to_string(i) + " digits") {
            return b.to_decimal_string();
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

    big_number b1 = big_number::binary("1");
    big_number b2 = big_number::binary("11");
    for (int i=4; i<=64; i*=4) {
        b1.set_binary_significand_precision(i*8);
        b2.set_binary_significand_precision(i*8);
        BENCHMARK("division - truncating after " + std::to_string(i) + " bytes") {
            return b1 / b2;
        };
    }
}
