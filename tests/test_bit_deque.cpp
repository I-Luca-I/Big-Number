#include <catch2/catch_test_macros.hpp>
#include "../include/bit_deque.h"

TEST_CASE("you can initialize a bit_deque from a std::string") {
    bit_deque b;
    REQUIRE(b.to_string() == "0");

    b = bit_deque("1");
    REQUIRE(b.to_string() == "1");

    b = bit_deque("101");
    REQUIRE(b.to_string() == "101");

    b = bit_deque("11111111");
    REQUIRE(b.to_string() == "11111111");

    b = bit_deque("1111111100000000");
    REQUIRE(b.to_string() == "1111111100000000");
}

TEST_CASE("you can push and pop bit in a bit_deque") {
    bit_deque b("101");
    REQUIRE(b.size() == 3);

    SECTION("pushing and popping bits back") {
        b.push_back(1);
        REQUIRE(b.to_string() == "1011");
        REQUIRE(b.size() == 4);

        for (int i=0; i<8; i++) {
            b.push_back(0);
        }
        REQUIRE(b.to_string() == "101100000000");
        REQUIRE(b.size() == 12);

        b.pop_back();
        REQUIRE(b.to_string() == "10110000000");
        REQUIRE(b.size() == 11);

        while (b.size() > 0) {
            b.pop_back();
        }
        REQUIRE(b.to_string() == "");
        REQUIRE(b.size() == 0);

        b.push_back(1);
        REQUIRE(b.to_string() == "1");
        REQUIRE(b.size() == 1);
    }

    SECTION("pushing and popping bits front") {
        b.push_front(1);
        REQUIRE(b.to_string() == "1101");
        REQUIRE(b.size() == 4);

        for (int i=0; i<8; i++) {
            b.push_front(0);
        }
        REQUIRE(b.to_string() == "000000001101");
        REQUIRE(b.size() == 12);

        b.pop_front();
        REQUIRE(b.to_string() == "00000001101");
        REQUIRE(b.size() == 11);

        while (b.size() > 0) {
            b.pop_front();
        }
        REQUIRE(b.to_string() == "");
        REQUIRE(b.size() == 0);

        b.push_front(1);
        REQUIRE(b.to_string() == "1");
        REQUIRE(b.size() == 1);
    }
}

TEST_CASE("you can set and get a single bit in a bit_deque") {
    bit_deque b("101");
    REQUIRE(b.size() == 3);

    SECTION("setting bits") {
        b.set(0, 0);
        REQUIRE(b.to_string() == "001");
        REQUIRE(b.size() == 3);

        b.set(2, 1);
        REQUIRE(b.to_string() == "001");
        REQUIRE(b.size() == 3);

        for (int i=0; i<b.size(); i++) {
            b.set(i, 1);
        }
        REQUIRE(b.to_string() == "111");
        REQUIRE(b.size() == 3);
    }

    SECTION("getting bits") {
        REQUIRE(b.get(0) == 1);
        REQUIRE(b.get(1) == 0);
        REQUIRE(b.get(2) == 1);
    }
}
