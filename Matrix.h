#ifndef MATRIX_h
#define MATRIX_h

#include <ostream>


struct Matrix
{
    size_t rows;
    size_t cols;

    double **data;

    Matrix();
    Matrix( size_t rows, size_t cols);
    Matrix( const Matrix & other);
    
    ~Matrix();

    void FillMagickSE();
    void WriteMatrix() const;
    void ReadMatrix();
    Matrix AddMatrix( const Matrix & other ) const;

    Matrix operator+( const Matrix & other ) const;
    Matrix operator-( const Matrix & other ) const;
        
};

std::ostream & operator<< (std::ostream & left, const Matrix & right);
Matrix operator* (double left, const Matrix & right);

#endif
