#include <catch2/catch_test_macros.hpp>
#include "../../include/big_number.h"

TEST_CASE("you can use all bitwise operators between two big_numbers") {
    big_number b1 = big_number::binary("101");
    big_number b2 = big_number::binary("11");
    big_number b3 = big_number::binary("10.001");
    big_number b4 = big_number::binary("-1001");
    
    SECTION("binary bitwise operators") {
        REQUIRE((b1 & b2).to_binary_string() == "001");
        REQUIRE((b1 | b2).to_binary_string() == "111");
        REQUIRE((b1 ^ b2).to_binary_string() == "110");

        REQUIRE((b3 & b4).to_binary_string() == "0000.000");
        REQUIRE((b3 | b4).to_binary_string() == "-1011.001");
        REQUIRE((b3 ^ b4).to_binary_string() == "-1011.001");
    }

    SECTION("unary bitwise operators") {
        REQUIRE((~b1).to_binary_string() == "-010");
        REQUIRE((~b2).to_binary_string() == "-00");

        REQUIRE((~b3).to_binary_string() == "-01.110");
        REQUIRE((~b4).to_binary_string() == "0110");
    }

    SECTION("bitshifting") {
        REQUIRE((b1 << 2).to_binary_string() == "10100");
        REQUIRE((b2 << 2).to_binary_string() == "1100");
        REQUIRE((b1 >> 2).to_binary_string() == "001.01");
        REQUIRE((b2 >> 2).to_binary_string() == "00.11");

        REQUIRE((b3 << 2).to_binary_string() == "1000.100");
        REQUIRE((b4 << 2).to_binary_string() == "-100100");
        REQUIRE((b3 >> 2).to_binary_string() == "00.10001");
        REQUIRE((b4 >> 2).to_binary_string() == "-0010.01");
    }
}
