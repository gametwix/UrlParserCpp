cmake_minimum_required(VERSION 3.12)
project("UrlCpp")

set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(googletest)

add_executable(UrlGParser gtests.cpp UrlParser.cpp)
target_link_libraries(UrlGParser gtest gtest_main)

add_executable(UrlSParser tests.cpp UrlParser.cpp)
