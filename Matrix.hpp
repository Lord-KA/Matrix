#ifndef MATRIX_h
#define MATRIX_h

#include <iostream>
#include <limits>
#include <cstddef>
#include <math.h>



class Matrix
{
    private:

        size_t rows;
        size_t cols;
        double determinant;

        double *matrix;


    public:
        Matrix();
        Matrix( size_t rows, size_t cols);
        Matrix( const Matrix & other);

        ~Matrix();

        void FillMagickSE();
        void WriteMatrix() const;
        void FillMatrix();
        void FillMatrixOp();
        Matrix AddMatrix( const Matrix & other ) const;
        double CalcDeterminant();
        Matrix GaussianMethod() const;

        Matrix Transposition() const;

        Matrix operator+( const Matrix & other ) const;
        Matrix operator*( const Matrix & other ) const;
        Matrix operator*( const double &n) const;
        Matrix& operator=( const Matrix & other );
        
        double operator() (const size_t i, const size_t j) const; 
        double& operator() (const size_t i, const size_t j); 

    friend std::ostream& operator<<(std::ostream &out, const Matrix &M);  
    friend Matrix operator*( const double &n, const Matrix &M);
};


Matrix operator*( const double &n, const Matrix &M );


#endif
