#include "../Matrix.hpp"

#include <chrono>
#include <vector>
#include <iostream>

static size_t counter = -1;

static constexpr size_t basicSize = 1e3;
static constexpr size_t passes = 1e1;

void test_0()
{  
    Matrix<int> M1(basicSize, basicSize), M2(basicSize, basicSize), M3;
    
    M1.FillMatrixRandom();
    M2.FillMatrixRandom();
    
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t cnt=0; cnt < passes; ++cnt){
    
        M3 = M1 + M2;
    
    }
    auto end = std::chrono::high_resolution_clock::now();
    ++counter;
    std::cout << "Test " << counter << " took " << std::chrono::duration<double, std::milli>(end - start).count() / passes << "ms\n";
}

void test_1()
{  
    Matrix<int> M1(basicSize, basicSize), M2(basicSize, basicSize), M3;
    
    M1.FillMatrixRandom();
    M2.FillMatrixRandom();

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t cnt=0; cnt < passes; ++cnt){

        M3 = M2 - M1;
    
    }
    auto end = std::chrono::high_resolution_clock::now();
    ++counter;
    std::cout << "Test " << counter << " took " << std::chrono::duration<double, std::milli>(end - start).count() / passes << "ms\n";
}

void test_2()
{
    Matrix<int> M1(basicSize, basicSize), M2(basicSize, basicSize), M3;
    
    M1.FillMatrixRandom();
    M2.FillMatrixRandom();

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t cnt=0; cnt < passes; ++cnt){
        
        M3 = M1 * M2;

    }
    auto end = std::chrono::high_resolution_clock::now();
    ++counter;
    std::cout << "Test " << counter << " took " << std::chrono::duration<double, std::milli>(end - start).count() / passes << "ms\n";
}

void test_3()
{
    Matrix<int> M1(basicSize, basicSize), M2(basicSize, basicSize), M3;
    
    M1.FillMatrixRandom();
    M2.FillMatrixRandom();

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t cnt=0; cnt < passes; ++cnt){
        
        M3 = M1;

    }    
    auto end = std::chrono::high_resolution_clock::now();
    ++counter;
    std::cout << "Test " << counter << " took " << std::chrono::duration<double, std::milli>(end - start).count() / passes << "ms\n";
}

void test_4()
{
    Matrix<int> M1(1e3, 1e3), M2(1e3, 1e3), M3;
    
    M1.FillMatrixRandom();
    M2.FillMatrixRandom();
    auto start = std::chrono::high_resolution_clock::now();
    
    M3 = M2;
    
    auto end = std::chrono::high_resolution_clock::now();
    ++counter;
    std::cout << "Test " << counter << " took " << std::chrono::duration<double, std::milli>(end - start).count() << "ms\n";
}




int main()
{
    #ifndef NTHREADS
    setThreadNum(4);
    #endif

    test_0();
    test_1();
    test_2();
    test_3();
    test_4();
}
