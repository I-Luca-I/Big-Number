include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.9.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(
    BigNumberTests
    ../srs/bit_deque.cpp
    ../srs/big_number/big_number.cpp
    ../srs/big_number/assignment_operators.cpp
    ../srs/big_number/binary_arithmetic_operators.cpp
    ../srs/big_number/unary_arithmetic_operators.cpp
    ../srs/big_number/relational_operators.cpp
    ../srs/big_number/bitwise_operators.cpp
    ../srs/big_number/rounding_functions.cpp

    test_bit_deque.cpp 
    big_number/test_big_number.cpp
    big_number/test_assignment_operators.cpp
    big_number/test_binary_arithmetic_operators.cpp
    big_number/test_unary_arithmetic_operators.cpp
    big_number/test_relational_operators.cpp
    big_number/test_bitwise_operators.cpp
    big_number/test_rounding_functions.cpp

)

target_link_libraries(BigNumberTests PRIVATE Catch2::Catch2WithMain)
