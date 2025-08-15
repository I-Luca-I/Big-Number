include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.9.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(
    BigNumberBenchmarks
    ../srs/bit_deque.cpp
    ../srs/big_number/big_number.cpp
    ../srs/big_number/assignment_operators.cpp
    ../srs/big_number/binary_arithmetic_operators.cpp
    ../srs/big_number/unary_arithmetic_operators.cpp
    ../srs/big_number/relational_operators.cpp
    ../srs/big_number/bitwise_operators.cpp

    benchmark_bit_deque.cpp
    benchmark_big_number.cpp
)

target_link_libraries(BigNumberBenchmarks PRIVATE Catch2::Catch2WithMain)
