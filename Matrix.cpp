#include "Matrix.hpp"

#include <limits>
#include <cmath>


double Matrix::operator() (const size_t i, const size_t j) const
{
    return matrix[i * cols + j];
}

double& Matrix::operator() (const size_t i, const size_t j)
{
    return matrix[i * cols + j];
}


std::ostream& operator<<(std::ostream &out, const Matrix &a)
{
    for (size_t i=0; i < a.rows; ++i){
        for (size_t j=0; j < a.cols; ++j)
            out << a(i, j) << ' ';
        out << '\n';
    }
    out << "\n";
    return out;
}


Matrix Matrix::operator+(const Matrix & other) const
{
    if(rows == other.rows && cols == other.cols){
        Matrix result = Matrix(other);
        for(size_t i=0; i < rows * cols; ++i)
            result.matrix[i] += matrix[i];
        return result; 
    }

    std::cerr << "Error: summaring matrixes of different sizes." << std::endl;
    exit(1);
}

Matrix Matrix::operator-(const Matrix & other) const
{
    if(rows == other.rows && cols == other.cols)
        return *this + -1 * other;
    
    std::cerr << "Error: subtracting matrixes of different sizes." << std::endl;
    exit(1);
}


Matrix Matrix::operator*(const Matrix & other) const
{
    if(cols == other.rows){
        Matrix result = Matrix(rows, cols);
        for(size_t i=0; i < rows; ++i)
            for(size_t j=0; j < cols; ++j){
                size_t sum = 0;
                for(size_t r=0; r < rows; ++r)
                    sum += (*this)(i, r) * other(r, j); 
                result(i, j) = sum;
            }
        return result;
    }

    std::cerr << "Error: bad input for multiplication." << std::endl;
    exit(1);
}

Matrix Matrix::operator*(const double &n) const
{
    Matrix result = Matrix(rows, cols);
    for(size_t i=0; i < rows * cols; ++i)
        result.matrix[i] = matrix[i] * n;
    return result;
}

Matrix operator*(const double &n, const Matrix &M)
{
    Matrix result = Matrix(M.rows, M.cols);
    for(size_t i=0; i < M.rows * M.cols; ++i)
        result.matrix[i] = M.matrix[i] * n;
    return result;
}


Matrix& Matrix::operator=( const Matrix &other)
{
    if (this == &other)
        return *this;

    rows = other.rows;
    cols = other.cols;

    //delete[] matrix;
    double *temp = matrix;

    try{
        matrix = new double[rows * cols];
        for(size_t i=0; i < rows*cols; ++i)
            matrix[i] = other.matrix[i];
        delete[] temp;
    }
    catch(...)
    {
        matrix = temp;
        std::cerr << "Error: memory allocation has failed." << std::endl;
    }

    return *this;
}


Matrix::Matrix()
{
    rows = 0;
    cols = 0;
    determinant = std::numeric_limits<double>::quiet_NaN();
    matrix = nullptr;
}

Matrix::~Matrix()
{
    delete[] matrix;

    matrix = nullptr;
}

Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;
    cols = other.cols;
    determinant = other.determinant;

    try{
        matrix = new double[rows * cols];

        for(size_t i = 0; i < rows * cols; ++i)
                matrix[i] = other.matrix[i];
    }
    catch(...)
    {
        std::cerr << "Error: memory allocation has failed." << std::endl;
    }
}

Matrix::Matrix(size_t r, size_t c)
{
    rows = r;
    cols = c;
    determinant = std::numeric_limits<double>::quiet_NaN();

    try{
        matrix = new double[rows * cols];
        for(size_t i=0; i < rows * cols; ++i)
            matrix[i] = 0;
    }
    catch(...)
    {
        std::cerr << "Error: memory allocation has failed." << std::endl;
    }
}


Matrix Matrix::Transposition() const
{
    Matrix result = Matrix(rows, cols);
    for(size_t i=0; i < rows; ++i)
        for(size_t j=0; j < cols; ++j)
            result(i, j) = (*this)(j, i); 
    return result;
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
    std::cout << Triangular;
    for(size_t i=0; i < rows; ++i)
        determinant += Triangular(i, i);

    return determinant;
}

Matrix Matrix::GaussianMethod() const
{
    Matrix result = Matrix(*this);
    
    for (size_t k=0; k < rows; ++k)
    {
        //for (size_t j=0; j < cols; ++j)
        //   result(k, j) /= (*this)(k, k);

        for (size_t i=k+1; i < rows; ++i)
        {
            double ratio = (*this)(k,k) / result(i, k);
            for (size_t j = 0; j < cols; ++j)
                result(i, j) -= result(k, j) * ratio;
        }
    }
    return result;
}


void Matrix::FillMagickSE()
{
    size_t cnt = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j){
            if (cols <= j + i){
                ++cnt;
                (*this)(i, j) = cnt; 
            }
    }
}

void Matrix::FillMatrix()
{
    size_t cnt = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
        {
            (*this)(i, j) = cnt; 
            ++cnt;
        }
}

void Matrix::FillMatrixOp()
{
    size_t cnt = rows * cols;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
        {
            (*this)(i, j) = cnt; 
            --cnt;
        }
}


void Matrix::WriteMatrix() const
{
    std::cout << rows << ' ' << cols << std::endl;

    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j)
            std::cout << (*this)(i, j) << ' '; 
        std::cout << std::endl;
    }
}



Matrix Matrix::AddMatrix(const Matrix &other) const
{
    return *this + other;
}
