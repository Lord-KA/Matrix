#include <limits>
#include <cmath>

template<typename T>
T Matrix<T>::operator() (const size_t i, const size_t j) const
{
    return matrix[i * cols + j];
}

template<typename T>
T& Matrix<T>::operator() (const size_t i, const size_t j)
{
    return matrix[i * cols + j];
}


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const
{
    if(rows == other.rows && cols == other.cols){
        Matrix<T> result = Matrix<T>(other);
        for(size_t i=0; i < rows * cols; ++i)
            result.matrix[i] += matrix[i];
        return result; 
    }

    std::cerr << "Error: summaring matrixes of different sizes." << std::endl;
    exit(1);
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const
{
    if(rows == other.rows && cols == other.cols)
        return *this + -1 * other;
    
    std::cerr << "Error: subtracting matrixes of different sizes." << std::endl;
    exit(1);
}


template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const
{
    if(cols == other.rows){
        Matrix<T> result = Matrix<T>(rows, cols);
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

template<typename T>
Matrix<T> Matrix<T>::operator*(const T &n) const
{
    Matrix<T> result = Matrix<T>(rows, cols);
    for(size_t i=0; i < rows * cols; ++i)
        result.matrix[i] = matrix[i] * n;
    return result;
}


template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &other)
{
    if (this == &other)
        return *this;

    rows = other.rows;
    cols = other.cols;

    //delete[] matrix;
    T *temp = matrix;

    try{
        matrix = new T[rows * cols];
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


template<typename T>
Matrix<T>::Matrix()
{
    rows = 0;
    cols = 0;
    determinant = std::numeric_limits<T>::quiet_NaN();
    matrix = nullptr;
}

template<typename T>
Matrix<T>::~Matrix()
{
    delete[] matrix;

    matrix = nullptr;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other)
{
    rows = other.rows;
    cols = other.cols;
    determinant = other.determinant;

    try{
        matrix = new T[rows * cols];

        for(size_t i = 0; i < rows * cols; ++i)
                matrix[i] = other.matrix[i];
    }
    catch(...)
    {
        std::cerr << "Error: memory allocation has failed." << std::endl;
    }
}

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c)
{
    rows = r;
    cols = c;
    determinant = std::numeric_limits<T>::quiet_NaN();

    try{
        matrix = new T[rows * cols];
        for(size_t i=0; i < rows * cols; ++i)
            matrix[i] = 0;
    }
    catch(...)
    {
        std::cerr << "Error: memory allocation has failed." << std::endl;
    }
}


template<typename T>
Matrix<T> Matrix<T>::Transposition() const
{
    Matrix<T> result = Matrix<T>(rows, cols);
    for(size_t i=0; i < rows; ++i)
        for(size_t j=0; j < cols; ++j)
            result(i, j) = (*this)(j, i); 
    return result;
}


template<typename T>
T Matrix<T>::CalcDeterminant()
{
    if (!std::isnan(determinant))
        return determinant;
    
    if (rows != cols) 
        return (*this).MinorsMethod();
    

    determinant = 1;
    Matrix<T> Triangular = (*this).GaussianMethod();
    if (Triangular.matrix == nullptr)
        return (*this).MinorsMethod();
    for(size_t i=0; i < rows; ++i)
        determinant *= Triangular(i, i);

    return determinant;
}

template<typename T>
Matrix<T> Matrix<T>::GaussianMethod() const
{
    Matrix<T> result = Matrix<T>(*this);
    int determinant_ratio = 1;
    for (size_t k=0; k < rows; ++k)
    {
        if (result(k, k) == 0){
            size_t i = k + 1;
            while (i < cols && result(k, i) == 0)
                ++i;
            if (i != cols){
                result.swapRows(k, i);
                determinant_ratio *= -1;
            }
            else
                return Matrix<T>();
        }
        
        for (size_t i=k+1; i < rows; ++i)
        {
            T ratio = result(i, k) / result(k, k);
            for (size_t j = 0; j < cols; ++j){
                result(i, j) -= result(k, j) * ratio;
                if (std::isnan(result(i, i))) //DEBUG
                    std::cout << "Error: ratio in GaussianMethod is none; {result(i, i), ratio, result(k, j)} = " << result(i, i) << ' ' << ratio << ' ' << result(k, j) << std::endl;
            }
        }
    }
    return result * determinant_ratio;
}

template<typename T>
void Matrix<T>::swapRows(size_t r_1, size_t r_2)
{
    for(size_t i=0; i<cols; ++i){
        T temp = (*this)(r_1, i);
        (*this)(r_1, i) = (*this)(r_2, i);
        (*this)(r_2, i) = temp;
    }
}

template<typename T>
T Matrix<T>::MinorsMethod() const
{
    T result = 0;
    if (rows==2 && cols==2) return (*this)(0,0) * (*this)(1,1) - (*this)(0, 1) * (*this)(1, 0);

    for(size_t i=0; i < rows; ++i){
        result += (*this)(0, i) * (i%2==0?1:-1) * (*this).Minor(0, i).MinorsMethod();
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::Minor(size_t i, size_t j) const
{
    Matrix<T> result(rows-1, cols-1);
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


template<typename T>
void Matrix<T>::FillMagickSE()
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

template<typename T>
void Matrix<T>::FillMatrix()
{
    size_t cnt = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
        {
            (*this)(i, j) = cnt; 
            ++cnt;
        }
}

template<typename T>
void Matrix<T>::FillMatrixOp()
{
    size_t cnt = rows * cols;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
        {
            (*this)(i, j) = cnt; 
            --cnt;
        }
}


template<typename T>
void Matrix<T>::WriteMatrix() const
{
    std::cout << rows << ' ' << cols << std::endl;

    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j)
            std::cout << (*this)(i, j) << ' '; 
        std::cout << std::endl;
    }
}


template<typename T>
void Matrix<T>::ReadMatrix()
{
    size_t r, c;
    std::cin >> r >> c;
    if (r != rows || c != cols)
    {
        delete[] matrix;
        matrix = nullptr;
        rows = r;
        cols = c;
        matrix = new T[rows * cols];
        }
    for(size_t i=0; i<rows; ++i)
        for(size_t j=0; j<cols; ++j)
            std::cin >> (*this)(i, j);
}


template<typename T>
Matrix<T> Matrix<T>::AddMatrix(const Matrix<T> &other) const
{
    return *this + other;
}
