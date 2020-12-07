#ifndef MATRIX_h
#define MATRIX_h

#include <iostream>
#include <vector>
#include <cstddef>


class Matrix
{
    private:

        size_t rows;
        size_t cols;

        double *matrix;

    public:
        Matrix();
        Matrix( size_t rows, size_t cols);
        Matrix( const Matrix & other);

        ~Matrix();

        void FillMagickSE();
        void WriteMatrix() const;
        Matrix AddMatrix( const Matrix & other ) const;

        Matrix operator+( const Matrix & other ) const;
        Matrix& operator=( const Matrix & other );
        
    friend std::ostream& operator<<(std::ostream &out, const Matrix &M);  
};



#endif
