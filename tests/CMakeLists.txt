cmake_minimum_required(VERSION 3.14)

project(Tests)

add_executable(matrix test-spmatrix.cpp ../Matrix.hpp spmatrix.hpp treap.hpp) 
add_executable(time test-time.cpp ../Matrix.hpp) 
add_executable(time-precise test-time-precise.cpp ../Matrix.hpp) 

target_link_libraries( 
    matrix 
    gtest_main 
) 

target_link_libraries(
    time
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix)
gtest_discover_tests(time)



