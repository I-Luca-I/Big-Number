#include <catch2/catch_test_macros.hpp>
#include "../../include/big_number.h"

TEST_CASE("big_number supports some assignment operations") {
    big_number b = big_number::binary("101");
    b += big_number::binary("101"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "1010");

    b += big_number::binary("11"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "1101");

    b -= big_number::binary("1000"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "101");

    b -= big_number::binary("1010"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "-101");

    b *= big_number::binary("1"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "-101");

    b *= big_number::binary("101.11"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "-11100.11");

    b /= big_number::binary("1"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "-11100.11");

    b /= big_number::binary("-1010"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "10.111");

    b = big_number::binary("100");
    b %= big_number::binary("1"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "0");

    b %= big_number::binary("101"); b.shrink_to_fit();
    REQUIRE(b.to_binary_string() == "0");
}
