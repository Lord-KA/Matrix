cmake_minimum_required(VERSION 3.14)

project(Tests)

add_executable(general-test test-spmatrix.cpp ../Matrix.hpp spmatrix.hpp treap.hpp) 
add_executable(benchmark test-time.cpp ../Matrix.hpp) 
add_executable(benchmark-precise test-time-precise.cpp ../Matrix.hpp) 

target_link_libraries( 
    general-test
    gtest_main 
) 

target_link_libraries(
    benchmark
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(general-test)
gtest_discover_tests(benchmark)
