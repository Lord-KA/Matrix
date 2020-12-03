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

Matrix Matrix::operator*(const Matrix & other) const
{
    Matrix result = Matrix(rows, cols);
    for(size_t i=0; i < rows; ++i)
        for(size_t j=0; j < cols; ++j){
            size_t sum = 0;
            for(size_t r=1; r <= rows; ++r)
                sum += matrix[i * cols + r] * other.matrix[r * cols + j];
            result.matrix[i * cols + j] = sum;
        }
    return result;
}

Matrix Matrix::operator*(const size_t n) const
{
    Matrix result = Matrix(rows, cols);
    for(size_t i=0; i < rows * cols; ++i)
        result.matrix[i] *= n;
    return result;
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

Matrix Matrix::Transposition() const
{
    Matrix result = Matrix(rows, cols);
    for(size_t i=0; i < rows; ++i)
        for(size_t j=0; j < cols; ++j)
            result.matrix[i * cols + j] = matrix[j * cols + i];
    return result;
}


Matrix::Matrix()
{
    rows = 0;
    cols = 0;
    determinant = 0;

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
    determinant = other.determinant;

    matrix = new double[rows * cols];

    for(size_t i = 0; i < rows * cols; ++i)
            matrix[i] = other.matrix[i];
}

Matrix::Matrix(size_t r, size_t c)
{
    rows = r;
    cols = c;
    determinant = std::numeric_limits<double>::quiet_NaN();
    matrix = new double[rows * cols];
    for(size_t i=0; i < rows * cols; ++i)
        matrix[i] = 0;
}


double Matrix::CalcDeterminant()
{
    if (rows != cols){
        std::cerr << "Error: matrix is not square" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    if (!std::isnan(determinant))
        return determinant;

    determinant = 0;
    Matrix Triangular = this->GaussianMethod();
    for(size_t i=0; i < rows; ++i)
        determinant += Triangular.matrix[i * rows + i];

    return determinant;
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



Matrix Matrix::AddMatrix(const Matrix &other) const
{
    //Matrix result;
    //result = *this + other;
    return *this + other;
}
