#include <catch2/catch_test_macros.hpp>
#include "../../include/big_number.h"

TEST_CASE("you can use all relational operators between two big_numbers") {
    big_number b1 = big_number::binary("101");
    big_number b2 = big_number::binary("11");
    REQUIRE((b1 > b2) == true);
    REQUIRE((b1 < b2) == false);
    REQUIRE((b1 == b2) == false);
    REQUIRE((b1 != b2) == true);
    REQUIRE((b1 >= b2) == true);
    REQUIRE((b1 <= b2) == false);

    b1 = big_number::binary("101");
    b2 = big_number::binary("101");
    REQUIRE((b1 > b2) == false);
    REQUIRE((b1 < b2) == false);
    REQUIRE((b1 == b2) == true);
    REQUIRE((b1 != b2) == false);
    REQUIRE((b1 >= b2) == true);
    REQUIRE((b1 <= b2) == true);

    b1 = big_number::binary("-101");
    b2 = big_number::binary("101");
    REQUIRE((b1 > b2) == false);
    REQUIRE((b1 < b2) == true);
    REQUIRE((b1 == b2) == false);
    REQUIRE((b1 != b2) == true);
    REQUIRE((b1 >= b2) == false);
    REQUIRE((b1 <= b2) == true);

    b1 = big_number::binary("-0");
    b2 = big_number::binary("0");
    REQUIRE((b1 > b2) == false);
    REQUIRE((b1 < b2) == false);
    REQUIRE((b1 == b2) == true);
    REQUIRE((b1 != b2) == false);
    REQUIRE((b1 >= b2) == true);
    REQUIRE((b1 <= b2) == true);

    b1 = big_number::binary("101.01");
    b2 = big_number::binary("101.100");
    REQUIRE((b1 > b2) == false);
    REQUIRE((b1 < b2) == true);
    REQUIRE((b1 == b2) == false);
    REQUIRE((b1 != b2) == true);
    REQUIRE((b1 >= b2) == false);
    REQUIRE((b1 <= b2) == true);

    b1 = big_number::binary("-101.11");
    b2 = big_number::binary("-101.10");
    REQUIRE((b1 > b2) == false);
    REQUIRE((b1 < b2) == true);
    REQUIRE((b1 == b2) == false);
    REQUIRE((b1 != b2) == true);
    REQUIRE((b1 >= b2) == false);
    REQUIRE((b1 <= b2) == true);
}
