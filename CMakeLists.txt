cmake_minimum_required(VERSION 3.14.0)
project(BigNumber VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.9.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(BigNumber srs/main.cpp srs/bit_deque.cpp)
add_executable(BigNumberTests tests/test_bit_deque.cpp srs/bit_deque.cpp)

target_link_libraries(BigNumberTests PRIVATE Catch2::Catch2WithMain)
