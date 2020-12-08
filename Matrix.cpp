#include "Matrix.h"

#include <iostream>

std::ostream& operator<<(std::ostream &out, const Matrix &a)
{
    for (size_t i=0; i < a.rows; ++i){
        for (size_t j=0; j < a.cols; ++j)
            out << a.data[i][j] << ' ';
        out << std::endl;
    }
    return out;
}


Matrix Matrix::operator+(const Matrix & other) const
{
    Matrix result = Matrix(rows, cols);
    for(size_t i=0; i < rows; ++i)
        for(size_t j=0; j < cols; ++j)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}

Matrix operator*(double N, const Matrix & right) 
{
    Matrix result = Matrix(right);
    for(size_t i=0; i < right.rows; ++i)
        for(size_t j=0; j < right.cols; ++j)
            result.data[i][j] *= N;
    return result;
}

Matrix Matrix::operator-(const Matrix & other) const
{
    return *this + -1 * other;
}


Matrix::Matrix()
{
    rows = 0;
    cols = 0;

    data = nullptr;
}


Matrix::~Matrix()
{  
    if (data != nullptr){
        for (size_t i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
        data = nullptr;
    }
}


Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;
    cols = other.cols;
    data = new double*[rows];

    for(size_t i = 0; i < rows; ++i)
    {
        data[i] = new double[cols];
        for(size_t j = 0; j < cols; ++j)
            data[i][j] = other.data[i][j];
    }
}

Matrix::Matrix(size_t r, size_t c)
{
    rows = r;
    cols = c;
    try{
    data = new double*[rows];
    for(size_t i=0; i < rows; ++i)
        data[i] = new double [cols];

    for(size_t i=0; i<rows; ++i)
        for(size_t j=0; j<cols; ++j)
            data[i][j] = 0;
    }
    catch(...)
    {
        std::cerr << "Error has appeared while allocating memory!" << std::endl;
        exit(1);
    }
}


void Matrix::FillMagickSE()
{
    size_t cnt = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j){
            std::cout << cols << ' ' << i << ' ' << j <<'\n';
            if (cols <= j + i){
                std::cout << '\n';
                ++cnt;
                data[i][j] = cnt;
            }
    }
    std::cout << '\n';
}


void Matrix::WriteMatrix() const
{
    std::cout << rows << ' ' << cols << std::endl;

    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j)
            std::cout << data[i][j] << ' ';
        std::cout << std::endl;
    }
}


Matrix Matrix::AddMatrix(const Matrix &other) const
{
    return *this + other;
}
