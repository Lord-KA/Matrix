#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream &out, const Matrix<T> &a)
{
    for (size_t i=0; i < a.rows; ++i){
        for (size_t j=0; j < a.cols; ++j)
            out << a.data[i][j] << ' ';
        out << std::endl;
    }
    return out;
}


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const
{
    Matrix<T> result = Matrix<T>(*this);
    for(size_t i=0; i < rows; ++i)
        for(size_t j=0; j < cols; ++j)
            result.data[i][j] += other.data[i][j];
    return result;
}

template<typename T>
Matrix<T> operator*(T N, const Matrix<T> & right) 
{
    Matrix<T> result = Matrix<T>(right);
    for(size_t i=0; i < right.rows; ++i)
        for(size_t j=0; j < right.cols; ++j)
            result.data[i][j] *= N;
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const
{
    return *this + -1 * other;
}


template<typename T>
Matrix<T>::Matrix()
{
    rows = 0;
    cols = 0;

    data = nullptr;
}


template<typename T>
Matrix<T>::~Matrix()
{  
    if (data != nullptr){
        for (size_t i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
        data = nullptr;
    }
}


template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other)
{
    rows = other.rows;
    cols = other.cols;
    data = new T*[rows];

    for(size_t i = 0; i < rows; ++i)
    {
        data[i] = new T[cols];
        for(size_t j = 0; j < cols; ++j)
            data[i][j] = other.data[i][j];
    }
}

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c)
{
    rows = r;
    cols = c;
    data = new T*[rows];
    for(size_t i=0; i < rows; ++i)
        data[i] = new T[cols];

    for(size_t i=0; i<rows; ++i)
        for(size_t j=0; j<cols; ++j)
            data[i][j] = 0;
}


template<typename T>
void Matrix<T>::FillMagickSE()
{
    size_t cnt = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j){
            if (cols <= j + i){
                ++cnt;
                data[i][j] = cnt;
            }
    }
}


template<typename T>
void Matrix<T>::WriteMatrix() const
{
    std::cout << rows << ' ' << cols << std::endl << *this;
}  


template<typename T>
Matrix<T> Matrix<T>::AddMatrix(const Matrix<T> &other) const
{
    return *this + other;
}


template<typename T>
void Matrix<T>::ReadMatrix()
{
    size_t r, c;
    std::cin >> r >> c;
    if (r != rows || c != cols)
    {
        if (data != nullptr){
                for (size_t i = 0; i < rows; ++i)
                    delete[] data[i];
                delete[] data;
            data = nullptr;
        }
        rows = r;
        cols = c;
        data = new T*[rows];
        for(size_t i=0; i < rows; ++i)
            data[i] = new T [cols];
    }
    for(size_t i=0; i<rows; ++i)
	    for(size_t j=0; j<cols; ++j)
	        std::cin >> data[i][j];
}

