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

TEST_CASE("two big_numbers can be multiplied") {
    big_number product = big_number::binary("0") * big_number::binary("0"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "0");

    product = big_number::binary("-1001") * big_number::binary("0"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "-0");

    product = big_number::binary("-1001.001") * big_number::binary("0"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "-0");

    product = big_number::binary("-1001") * big_number::binary("1"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "-1001");

    product = big_number::binary("-1001.001") * big_number::binary("1"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "-1001.001");

    product = big_number::binary("-1001") * big_number::binary("10"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "-10010");

    product = big_number::binary("-1001") * big_number::binary("100"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "-100100");

    product = big_number::binary("-1001.001") * big_number::binary("10"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "-10010.01");

    product = big_number::binary("-1001.001") * big_number::binary("100"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "-100100.1");

    product = big_number::binary("-1001") * big_number::binary("101"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "-101101");

    product = big_number::binary("-1001") * big_number::binary("-101"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "101101");

    product = big_number::binary("10011.0101") * big_number::binary("11.01"); product.shrink_to_fit();
    REQUIRE(product.to_binary_string() == "111110.110001");
}

TEST_CASE("two big_numbers can be divided") {
    big_number quotient = big_number::binary("1") / big_number::binary("1"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "1");

    quotient = big_number::binary("101") / big_number::binary("1"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "101");

    quotient = big_number::binary("101.101") / big_number::binary("-101.101"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "-1");

    quotient = big_number::binary("0") / big_number::binary("1"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "0");

    quotient = big_number::binary("0") / big_number::binary("101.101"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "0");

    quotient = big_number::binary("1111") / big_number::binary("101"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "11");

    quotient = big_number::binary("1111") / big_number::binary("10"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "111.1");

    quotient = big_number::binary("1101") / big_number::binary("11"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "100.0101010101010101010101010101010101");

    quotient = big_number::binary("101") / big_number::binary("1111"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "0.0101010101010101010101010101010101");

    quotient = big_number::binary("1001110101101.001101011100001010001111010111000010100011110101110000101000") / big_number::binary("1100110111.000110011001100110011001100110011001100110011001100110011001"); quotient.shrink_to_fit();
    REQUIRE(quotient.to_binary_string() == "110.0001111010101011011010111110000101");
}

TEST_CASE("two big_numbers can be moduled") {
    big_number mod = big_number::binary("1") % big_number::binary("1"); mod.shrink_to_fit();
    REQUIRE(mod.to_binary_string() == "0");

    mod = big_number::binary("101") % big_number::binary("1"); mod.shrink_to_fit();
    REQUIRE(mod.to_binary_string() == "0");

    mod = big_number::binary("101") % big_number::binary("10"); mod.shrink_to_fit();
    REQUIRE(mod.to_binary_string() == "1");

    mod = big_number::binary("101") % big_number::binary("-10"); mod.shrink_to_fit();
    REQUIRE(mod.to_binary_string() == "1");

    mod = big_number::binary("-101") % big_number::binary("10"); mod.shrink_to_fit();
    REQUIRE(mod.to_binary_string() == "-1");

    mod = big_number::binary("-101") % big_number::binary("-10"); mod.shrink_to_fit();
    REQUIRE(mod.to_binary_string() == "-1");

    mod = big_number::binary("1010") % big_number::binary("10"); mod.shrink_to_fit();
    REQUIRE(mod.to_binary_string() == "0");

    mod = big_number::binary("1101101") % big_number::binary("110011"); mod.shrink_to_fit();
    REQUIRE(mod.to_binary_string() == "111");
}
