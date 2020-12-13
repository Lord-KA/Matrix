#ifndef MATRIX_h
#define MATRIX_h

#include <iostream>
#include <cstddef>

template<typename T>
class Matrix
{
    private:

        size_t rows;
        size_t cols;
        T determinant;

        T *matrix;


    public:
        Matrix();
        Matrix( size_t rows, size_t cols);
        Matrix( const Matrix & other);

        ~Matrix();

        void FillMagickSE();
        void WriteMatrix() const;
        void ReadMatrix();
        void FillMatrix();
        void FillMatrixOp();
        Matrix AddMatrix( const Matrix & other ) const;
        T CalcDeterminant();
        Matrix GaussianMethod() const;
        void swapRows(size_t i, size_t j);
        T MinorsMethod() const;
        Matrix Minor(size_t i, size_t j) const;

        Matrix Transposition() const;

        Matrix operator+( const Matrix & other ) const;
        Matrix operator-( const Matrix & other ) const;
        Matrix operator*( const Matrix & other ) const;
        Matrix operator*( const T &n) const;
        Matrix& operator=( const Matrix & other );
        
        T operator() (const size_t i, const size_t j) const; 
        T& operator() (const size_t i, const size_t j); 

    friend std::ostream& operator<<(std::ostream &out, const Matrix &a)
    {    
        for (size_t i=0; i < a.rows; ++i){
            for (size_t j=0; j < a.cols; ++j)
                out << a(i, j) << ' ';
            out << '\n';
        }
        out << "\n";
        return out;
    }

    friend Matrix operator*( const T &n, const Matrix &M)
    {
        Matrix<T> result = Matrix<T>(M.rows, M.cols);
        for(size_t i=0; i < M.rows * M.cols; ++i)
           result.matrix[i] = M.matrix[i] * n;
        return result;
    }

};

#include "Matrix.cpp"
#endif
