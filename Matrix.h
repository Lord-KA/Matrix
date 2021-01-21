#include <ostream>

template <typename T> class Matrix;

template <typename T>
std::ostream & operator<< ( std::ostream & left, const Matrix<T> & right );

template <typename T>
Matrix<T> operator* ( T left, const Matrix<T> & right );

template <typename T> 
class Matrix
{
 private:
  size_t rows; //количество строк
  size_t cols; //количество столбцов
  
  T **data; //элементы матрицы
  
 public:
  Matrix(size_t rows, size_t cols);
  
  void WriteMatrix() const ; //вывод числа строк, столбцов, элементов
  
  void FillMagickSE(); // 201
  
  Matrix();
 ~Matrix();
  Matrix(const Matrix<T> & other);
  
  Matrix<T> AddMatrix(const Matrix<T> & other) const;
  
  void ReadMatrix();

  Matrix<T> operator+ ( const Matrix<T> & right ) const;
  Matrix<T> operator- ( const Matrix<T> & right ) const;

  friend std::ostream & operator<< <T>( std::ostream & left, const Matrix<T> & right );
  friend Matrix<T> operator* <T>( T left, const Matrix<T> & right );
};

#include "Matrix.cpp"
