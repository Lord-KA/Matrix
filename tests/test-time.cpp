#include "../Matrix.hpp"
#include <random>
#include <gtest/gtest.h>

std::mt19937 rnd(179);

constexpr size_t n = 2;
constexpr size_t k = 17;

constexpr size_t multiplicationLim = 2000;
constexpr size_t subtractionLim = 4000;
constexpr size_t passes = 100;
constexpr size_t passesSum = 10;

TEST(Manual, Basic)
{
    #ifndef NTHREADS
    setThreadNum(4);
    #endif  
    Matrix<int> M1(10, 10), M2(10, 10), M3;
    M1.FillMatrixRandom();
    M2.FillMatrixRandom();
    
    M3 = M1 * M2;
    //std::cout << M1 << '\n';
}

TEST(Multiplication, RandomSquares) {
    for(int i = 0; i < passes; ++i){
        int a = rnd() % (multiplicationLim / 3) + 4;
        Matrix<int> M1(a, a), M2(a, a), M3;
        M1.FillMatrixRandom();
        M2.FillMatrixRandom();
        M3 = M1 * M2;   
   }
}

TEST(Multiplication, RandomDiffSize) {
    for(int i = 0; i < passes; ++i){
        int a = rnd() % multiplicationLim + 3, b = rnd() % multiplicationLim + 3, c = rnd() % 15 + 3;
        Matrix<int> M1(a, b), M2(b, c), M3;
        M1.FillMatrixRandom();
        M2.FillMatrixRandom();
        M3 = M1 * M2;
    }
}


TEST(Summing, Manual) {
    for(int i = 0; i < passes / 100; ++i){
        int a = subtractionLim + 1324;
        Matrix<int> M1(a, a), M2(a, a), M3;
        M1.FillMatrixRandom();
        M2.FillMatrixRandom();
    
        for (int q = 0; q < passesSum; ++q)
            M3 = M1 + M2;
   }
}

TEST(Summing, RandomSquares) {
    for(int i = 0; i < passes / 10; ++i){
        int a = rnd() % subtractionLim + 3, b = rnd() % subtractionLim + 3;
        Matrix<int> M1(a, a), M2(a, a), M3;
        M1.FillMatrixRandom();
        M2.FillMatrixRandom();
    
        for (int q = 0; q < passes; ++q)
            M3 = M1 + M2;
   }
}

TEST(Summing, RandomDiffSize) {
    for(int i = 0; i < passes / 10; ++i){
        int a = rnd() % subtractionLim + 3, b = rnd() % subtractionLim + 3;
        Matrix<int> M1(a, b), M2(a, b), M3;
        M1.FillMatrixRandom();
        M2.FillMatrixRandom();
    
        for (int q = 0; q < passes; ++q)
            M3 = M1 + M2;
   }
}

TEST(Summing, RandomDiffSizeSubraction) {
    for(int i = 0; i < passes / 10; ++i){
        int a = rnd() % subtractionLim + 3, b = rnd() % subtractionLim + 3;
        Matrix<int> M1(a, b), M2(a, b), M3;
        M1.FillMatrixRandom();
        M2.FillMatrixRandom();
        
        for (int q = 0; q < 100; ++q)
            M3 = M1 + M2;
    }
}

TEST(Summing, RandomMultiplByConst) {
    size_t cnst = rnd();
    for(int i = 0; i < passes; ++i){
        int a = rnd() % subtractionLim + 3, b = rnd() % subtractionLim + 3;
        Matrix<int> M1(a, b), M2(a, b), M3;
        M1.FillMatrixRandom();
        M2.FillMatrixRandom();
    
        M3 = M1 + M2 * cnst;
        M3 = -M3;
   }
}

TEST(Other, Transposing) {
    for(int i = 0; i < passes; ++i){
        int a = rnd() % multiplicationLim + 3, b = rnd() % multiplicationLim + 3;
        Matrix<int> M1(a, b), M2(a, b), M3;
        M1.FillMatrixRandom();
        M2.FillMatrixRandom();
    
        M3 = M1.Transposition();
    }
}

TEST(Other, Copy) {                     
    for (int i = 0; i < passes; ++i){
        Matrix<int> M1(4, 18);
        M1.FillMatrixRandom();
        Matrix<int> M2(M1);
        M2.FillMatrixRandom();
        Matrix<int> M3 = M1 + M2;
        Matrix<int> M4(M3 + M1);

        Matrix<int> M5;
        M5 = M1 * 17 + M3;
        M5 = M5 + M4;
        M5 = M5 - M3;
        
        Matrix<int> MM1(12, 23), MM2(23, 19);
        MM1.FillMatrixRandom();
        MM2.FillMatrixRandom();
        MM1 = MM1 * MM2;
        MM1 = MM1 * 127 * i;
    }

}

TEST(Other, Move) {
    for (int i = 0; i < passes; ++i){
        Matrix<int> M1(18, 39), M2, M3, M4;
        M1.FillMatrixRandom();
        M2 = M1;
        M2.FillMatrixRandom();
        M3 = std::move(M1);
        M4 = std::move(M2);
    
        Matrix<int> M5(std::move(M3));
    }     
}

