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
    if (!std::isnan(determinant))
        return determinant;
    
    if (rows != cols && false) // GaussianMethod doesn't work consistantly.
        return (*this).MinorsMethod();
    

    determinant = 1;
    Matrix Triangular = (*this).GaussianMethod();
    if (Triangular.matrix == nullptr)
        return (*this).MinorsMethod();
    // std::cout << Triangular << std::endl; //DEBUG
    for(size_t i=0; i < rows; ++i)
        determinant *= Triangular(i, i);

    return determinant;
}

Matrix Matrix::GaussianMethod() const
{
    Matrix result = Matrix(*this);
    size_t determinant_ratio = 1;
    for (size_t k=0; k < rows; ++k)
    {
        // std::cout << result << std::endl; //DEBUG
        /*
        if (result(k, k) == 0){
            size_t i = k + 1;
            while (result(k, i) == 0)
                ++i;
            if (i != cols){
                result.swapRows(k, i);
                determinant_ratio *= -1;
            }
            else
                return Matrix();
        }
        */
        for (size_t i=k+1; i < rows; ++i)
        {
            double ratio = result(i, k) / result(k, k);
            for (size_t j = 0; j < cols; ++j)
                if (result(k, j) && ratio && !std::isnan(result(k, j)) && !std::isnan(ratio)){ // check to protect from NaN; TODO think of some boundary values
                    result(i, j) -= result(k, j) * ratio;
                    if (std::isnan(result(i, i))) //DEBUG
                        std::cout << "######" << result(i, i) << ' ' << ratio << ' ' << result(k, j) << std::endl;
                }
        }
    }
    return result * determinant_ratio;
}

void Matrix::swapRows(size_t r_1, size_t r_2)
{
    for(size_t i=0; i<cols; ++i){
        double temp = (*this)(r_1, i);
        (*this)(r_1, i) = (*this)(r_2, i);
        (*this)(r_2, i) = temp;
    }
}

double Matrix::MinorsMethod() const
{
    double result = 0;
    if (rows==2 && cols==2) return (*this)(0,0) * (*this)(1,1) - (*this)(0, 1) * (*this)(1, 0);

    for(size_t i=0; i < rows; ++i){
        result += (*this)(0, i) * (i%2==0?1:-1) * (*this).Minor(0, i).MinorsMethod();
        // std::cout << i << std::endl; //DEBUG
        // std::cout << (*this).Minor(0, i) << std::endl; //DEBUG
    }
    return result;
}

Matrix Matrix::Minor(size_t i, size_t j) const
{
    Matrix result(rows-1, cols-1);
    bool flag_r = false;
    for(size_t r=0; r<rows-1; ++r){
        bool flag_c = false;
        for(size_t c=0; c<cols-1; ++c){
            if (r == i) flag_r = true;
            if (c == j) flag_c = true;
        
            result(r, c) = (*this)(r + flag_r, c + flag_c);
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


void Matrix::ReadMatrix()
{
    size_t r, c;
    std::cin >> r >> c;
    if (r != rows || c != cols)
    {
        delete[] matrix;
        matrix = nullptr;
        rows = r;
        cols = c;
        matrix = new double[rows * cols];
        }
    for(size_t i=0; i<rows; ++i)
        for(size_t j=0; j<cols; ++j)
            std::cin >> (*this)(i, j);
}


Matrix Matrix::AddMatrix(const Matrix &other) const
{
    return *this + other;
}
