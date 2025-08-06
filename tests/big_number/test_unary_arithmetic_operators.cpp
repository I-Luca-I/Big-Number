#include <catch2/catch_test_macros.hpp>
#include "../../include/big_number.h"

TEST_CASE("big_number supports all unary arithmetic operations") {
    big_number b = big_number::binary("1010");
    REQUIRE((+b).to_binary_string() == "1010");
    REQUIRE((-b).to_binary_string() == "-1010");
    b.shrink_to_fit();

    REQUIRE((b++).to_binary_string() == "1010");
    REQUIRE(b.to_binary_string() == "001011");
    b.shrink_to_fit();

    REQUIRE((b--).to_binary_string() == "1011");
    REQUIRE(b.to_binary_string() == "001010");
    b.shrink_to_fit();

    REQUIRE((++b).to_binary_string() == "001011");
    REQUIRE(b.to_binary_string() == "001011");
    b.shrink_to_fit();

    REQUIRE((--b).to_binary_string() == "001010");
    REQUIRE(b.to_binary_string() == "001010");
}