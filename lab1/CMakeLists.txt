cmake_minimum_required(VERSION 3.26)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(BitArrayTest bitarray_test.cpp BitArray.cpp)

target_link_libraries(BitArrayTest gtest gtest_main)

add_test(NAME BitArrayTest COMMAND BitArrayTest)
