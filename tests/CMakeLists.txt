cmake_minimum_required(VERSION 3.14)

project(Tests)

add_executable(matrix test-spmatrix.cpp ../Matrix.hpp spmatrix.hpp treap.hpp) 
#set_source_files_properties(test-spmatrix.cpp PROPERTIES COMPILE_FLAGS "-Wpedantic -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g")
add_executable(time test-time.cpp ../Matrix.hpp) 
#set_source_files_properties(test-time.cpp PROPERTIES COMPILE_FLAGS "-D NDEBUG")

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



