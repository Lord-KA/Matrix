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
    if(rows == other.rows && cols == other.cols){
        Matrix result = Matrix(other);
        for(size_t i=0; i < rows * cols; ++i)
            result.matrix[i] += matrix[i];
        return result; 
    }

    std::cerr << "Error: summaring matrixes of different sizes." << std::endl;
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
                    sum += matrix[i * cols + r] * other.matrix[r * cols + j];
                result.matrix[i * cols + j] = sum;
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

Matrix Matrix::GaussianMethod() const
{
    return Matrix();
}


void Matrix::FillMagickSE()
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


void Matrix::FillMatrix()
{
    size_t cnt = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
        {
            matrix[i * cols + j] = cnt;
            ++cnt;
        }
}


void Matrix::FillMatrixOp()
{
    size_t cnt = rows * cols - 1;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
        {
            matrix[i * cols + j] = cnt;
            --cnt;
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
    return *this + other;
}
