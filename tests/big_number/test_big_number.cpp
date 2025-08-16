#include <catch2/catch_test_macros.hpp>
#include "../../include/big_number.h"

TEST_CASE("you can initialize a big_number from a binary string") {
    big_number b = big_number::binary("1");
    REQUIRE(b.to_binary_string() == "1");
    REQUIRE(b.size() == 1);

    b = big_number::binary("101");
    REQUIRE(b.to_binary_string() == "101");
    REQUIRE(b.size() == 3);

    b = big_number::binary("-0101");
    REQUIRE(b.to_binary_string() == "-0101");
    REQUIRE(b.size() == 4);

    b = big_number::binary("101.101");
    REQUIRE(b.to_binary_string() == "101.101");
    REQUIRE(b.size() == 6);

    b = big_number::binary("-1011.00");
    REQUIRE(b.to_binary_string() == "-1011.00");
    REQUIRE(b.size() == 6);
}

TEST_CASE("a big_number can be resized") {
    big_number b = big_number::binary("1011.1011");

    SECTION("resizing the integer part") {
        b.resize_integer(8);
        REQUIRE(b.to_binary_string() == "00001011.1011");
        REQUIRE(b.size() == 12);

        b.resize_integer(6);
        REQUIRE(b.to_binary_string() == "001011.1011");
        REQUIRE(b.size() == 10);

        b.resize_integer(2);
        REQUIRE(b.to_binary_string() == "1011.1011");
        REQUIRE(b.size() == 8);

        b.resize_integer(0);
        REQUIRE(b.to_binary_string() == "1011.1011");
        REQUIRE(b.size() == 8);
    }

    SECTION("resizing the fractional part") {
        b.resize_fraction(8);
        REQUIRE(b.to_binary_string() == "1011.10110000");
        REQUIRE(b.size() == 12);

        b.resize_fraction(6);
        REQUIRE(b.to_binary_string() == "1011.101100");
        REQUIRE(b.size() == 10);

        b.resize_fraction(2);
        REQUIRE(b.to_binary_string() == "1011.10");
        REQUIRE(b.size() == 6);

        b.resize_fraction(0);
        REQUIRE(b.to_binary_string() == "1011");
        REQUIRE(b.size() == 4);
    }

    SECTION("shrinking to fit") {
        b.shrink_to_fit();
        REQUIRE(b.to_binary_string() == "1011.1011");
        REQUIRE(b.size() == 8);

        b = big_number::binary("0010.0010");
        b.shrink_to_fit();
        REQUIRE(b.to_binary_string() == "10.001");
        REQUIRE(b.size() == 5);

        b = big_number::binary("0000.0010");
        b.shrink_to_fit();
        REQUIRE(b.to_binary_string() == "0.001");
        REQUIRE(b.size() == 4);

        b = big_number::binary("0010.0000");
        b.shrink_to_fit();
        REQUIRE(b.to_binary_string() == "10");
        REQUIRE(b.size() == 2);
    }

    SECTION("resizing two objects to have the same size") {
        big_number b1 = big_number::binary("-1001.01");
        big_number b2 = big_number::binary("10.01110");
        big_number::equalize_sizes(b1, b2);
        REQUIRE(b1.to_binary_string() == "-1001.01000");
        REQUIRE(b2.to_binary_string() == "0010.01110");
        REQUIRE(b1.size() == b2.size());

        b1 = big_number::binary("-1001.01");
        b2 = big_number::binary("-1110");
        big_number::equalize_sizes(b1, b2);
        REQUIRE(b1.to_binary_string() == "-1001.01");
        REQUIRE(b2.to_binary_string() == "-1110.00");
        REQUIRE(b1.size() == b2.size());
    }
}

TEST_CASE("you can limit the size of a big_number's fractional part") {
    big_number b = big_number::binary("1011.1011");
    REQUIRE(b.to_binary_string() == "1011.1011");

    b.set_binary_significand_precision(2);
    REQUIRE(b.to_binary_string() == "1011.10");

    b.set_binary_significand_precision(0);
    REQUIRE(b.to_binary_string() == "1011");

    b.set_binary_significand_precision(4);
    REQUIRE(b.to_binary_string() == "1011.1011");
}