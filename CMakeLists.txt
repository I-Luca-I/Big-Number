cmake_minimum_required(VERSION 3.14.0)
project(BigNumber VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.9.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(
    BigNumber 
    srs/main.cpp 
    srs/bit_deque.cpp
    srs/big_number/big_number.cpp
    srs/big_number/bitwise_operators.cpp
    srs/big_number/relational_operators.cpp
)

add_executable(
    BigNumberTests
    srs/bit_deque.cpp
    srs/big_number/big_number.cpp
    srs/big_number/bitwise_operators.cpp
    srs/big_number/relational_operators.cpp

    tests/test_bit_deque.cpp 
    tests/big_number/test_big_number.cpp
    tests/big_number/test_bitwise_operators.cpp
    tests/big_number/test_relational_operators.cpp
)

target_link_libraries(BigNumberTests PRIVATE Catch2::Catch2WithMain)
