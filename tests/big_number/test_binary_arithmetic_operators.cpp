#include <catch2/catch_test_macros.hpp>
#include "../../include/big_number.h"

TEST_CASE("two big_numbers can be summed") {
    big_number sum = big_number::binary("101") + big_number::binary("101"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "1010");

    sum = big_number::binary("1010") + big_number::binary("1"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "1011");

    sum = big_number::binary("1010.01") + big_number::binary("0011"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "1101.01");

    sum = big_number::binary("1.01") + big_number::binary("11.11"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "101");

    sum = big_number::binary("101") + big_number::binary("-101"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "0");

    sum = big_number::binary("1010") + big_number::binary("-1"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "1001");

    sum = big_number::binary("-101") + big_number::binary("-101"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "-1010");

    sum = big_number::binary("-1010") + big_number::binary("-1"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "-1011");

    sum = big_number::binary("101") + big_number::binary("-1010"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "-101");
}

TEST_CASE("two big_numbers can be subtracted") {
    big_number sum = big_number::binary("101") - big_number::binary("010"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "11");

    sum = big_number::binary("1010") - big_number::binary("-101"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "1111");

    sum = big_number::binary("101") - big_number::binary("1010"); sum.shrink_to_fit();
    REQUIRE(sum.to_binary_string() == "-101");
}
