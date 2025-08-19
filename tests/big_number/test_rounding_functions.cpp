#include <catch2/catch_test_macros.hpp>
#include "../../include/big_number.h"

TEST_CASE("you can use all rounding functions on big_numbers") {
    big_number value[6] = {
        big_number::decimal("2.3"), 
        big_number::decimal("3.8"), 
        big_number::decimal("5.5"), 
        big_number::decimal("-2.3"), 
        big_number::decimal("-3.8"), 
        big_number::decimal("-5.5")
    };

    REQUIRE(big_number::round(value[0]).to_decimal_string() == "2");
    REQUIRE(big_number::round(value[1]).to_decimal_string() == "4");
    REQUIRE(big_number::round(value[2]).to_decimal_string() == "6");
    REQUIRE(big_number::round(value[3]).to_decimal_string() == "-2");
    REQUIRE(big_number::round(value[4]).to_decimal_string() == "-4");
    REQUIRE(big_number::round(value[5]).to_decimal_string() == "-6");

    REQUIRE(big_number::floor(value[0]).to_decimal_string() == "2");
    REQUIRE(big_number::floor(value[1]).to_decimal_string() == "3");
    REQUIRE(big_number::floor(value[2]).to_decimal_string() == "5");
    REQUIRE(big_number::floor(value[3]).to_decimal_string() == "-3");
    REQUIRE(big_number::floor(value[4]).to_decimal_string() == "-4");
    REQUIRE(big_number::floor(value[5]).to_decimal_string() == "-6");

    REQUIRE(big_number::ceil(value[0]).to_decimal_string() == "3");
    REQUIRE(big_number::ceil(value[1]).to_decimal_string() == "4");
    REQUIRE(big_number::ceil(value[2]).to_decimal_string() == "6");
    REQUIRE(big_number::ceil(value[3]).to_decimal_string() == "-2");
    REQUIRE(big_number::ceil(value[4]).to_decimal_string() == "-3");
    REQUIRE(big_number::ceil(value[5]).to_decimal_string() == "-5");

    REQUIRE(big_number::trunc(value[0]).to_decimal_string() == "2");
    REQUIRE(big_number::trunc(value[1]).to_decimal_string() == "3");
    REQUIRE(big_number::trunc(value[2]).to_decimal_string() == "5");
    REQUIRE(big_number::trunc(value[3]).to_decimal_string() == "-2");
    REQUIRE(big_number::trunc(value[4]).to_decimal_string() == "-3");
    REQUIRE(big_number::trunc(value[5]).to_decimal_string() == "-5");
}
