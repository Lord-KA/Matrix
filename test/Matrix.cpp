#include "Matrix.h"

std::ostream& operator<<(std::ostream &out, const Matrix &a)
{
    for (size_t i=0; i < a.rows; ++i){
        for (size_t j=0; j < a.cols; ++j)
            out << a.matrix[i * a.cols + j] << ' ';
        out << '\n';
    }
    out << "\n";
    return out;
}

Matrix Matrix::operator+(const Matrix & other) const
{
    Matrix result = Matrix(rows, cols);
    for(size_t i=0; i < rows; ++i)
        for(size_t j=0; j < cols; ++j)
            result.matrix[i * cols + j] = matrix[i * cols + j] + other.matrix[i * cols + j];
    return result;
}


Matrix::Matrix()
{
    rows = 0;
    cols = 0;

    matrix = nullptr;
}


Matrix::~Matrix()
{
    if (matrix != nullptr)
        delete[] matrix;

    matrix = nullptr;
}


Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;
    cols = other.cols;
    matrix = new double[rows * cols];

    for(size_t i = 0; i < rows * cols; ++i)
            matrix[i] = other.matrix[i];
}

Matrix::Matrix(size_t r, size_t c)
{
    rows = r;
    cols = c;
    matrix = new double[rows * cols];
    for(size_t i=0; i < rows * cols; ++i)
        matrix[i] = 0;
}


void Matrix::FillMatrickSE()
{
    size_t cnt = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j){
            if (cols <= j + i){
                ++cnt;
                matrix[i * cols + j] = cnt;
            }
    }
}


void Matrix::WriteMatrix() const
{
    std::cout << rows << ' ' << cols << std::endl;

    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j)
            std::cout << matrix[i * cols + j] << ' ';
        std::cout << std::endl;
    }
}


Matrix& Matrix::operator=( const Matrix &other)
{
    if (this == &other)
        return *this;

    rows = other.rows;
    cols = other.cols;

    delete[] matrix;

    matrix = new double[rows * cols];
    for(size_t i=0; i < rows*cols; ++i)
        matrix[i] = other.matrix[i];

    return *this;
}


Matrix Matrix::AddMatrix(const Matrix &other) const
{
    //Matrix result;
    //result = *this + other;
    return *this + other;
}
