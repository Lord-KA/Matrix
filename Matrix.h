/* Аудиторная работа №4 23-28 11.2020 */

#ifndef  Matrix_h
#define  Matrix_h

// Аудиторная работа №6 7-12 12.2020
//#include <cstddef>
#include <ostream>

struct Matrix
{
  size_t rows; //количество строк
  size_t cols; //количество столбцов
  
  double **data; //элементы матрицы
  
  Matrix(size_t rows, size_t cols);
  
  void WriteMatrix() const ; //вывод числа строк, столбцов, элементов
  
  void FillMagick();   // DEBUG
  
  void FillMagickNE(); // 203
  void FillMagickSW(); // 204
  void FillMagickNW(); // 202
  void FillMagickSE(); // 201
  void FillMagickDD(); // 205
  
  /* Аудиторная работа №5 30-5 11-12.2020 */
  Matrix();
 ~Matrix();
  Matrix(const Matrix & other);
  
  Matrix AddMatrix(const Matrix & other) const;
  
  /* Аудиторная работа №6 7-12 12.2020 */
  void ReadMatrix();

  Matrix operator+ ( const Matrix & right ) const;
  Matrix operator- ( const Matrix & right ) const;
};

/* Аудиторная работа №6 7-12 12.2020 */
std::ostream & operator<< ( std::ostream & left, const Matrix & right );

Matrix operator* ( double left, const Matrix & right );

#endif //Matrix_h
