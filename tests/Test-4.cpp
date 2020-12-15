#include "Matrix.h"

#include <iostream>

int main()
{
  Matrix m1(8,4);
  m1.FillMagickSE();
  	//std::cerr << "--- m1 ---" << std::endl << m1 ;
  Matrix m2;
  m2.ReadMatrix();
  	//std::cerr << "--- m2 ---" << std::endl << m2 ;
  
  Matrix m3 = m2 + m1;
  	//std::cerr << "--- m3 ---" << std::endl << m3 ;
  
  m1.ReadMatrix();
  Matrix m4 = m1 - m2;
  	//std::cerr << "--- m4 ---" << std::endl << m4 ;
  
  Matrix m5;
  m5.ReadMatrix();
  	//std::cerr << "--- m5 ---" << std::endl << m5 ;
  
  Matrix m6 = m5 + m2 - m1 + m3 - m4;
  	//std::cerr << "--- m6 ---" << std::endl << m6 ;
  
  Matrix m7 = (m5.ReadMatrix(),m5) 
            + (m1.ReadMatrix(),m1)
            - (m2.ReadMatrix(),m2)
            + m3 - m4 + m6 ;
  	//std::cerr << "--- m7 ---" << std::endl << m7 ;
  
  Matrix m8 = m5 + 3.14*(m5.ReadMatrix(),m5) 
            + m1 - 2.67*(m1.ReadMatrix(),m1)
            - m2 + 1.16*(m2.ReadMatrix(),m2)
            + m3 - m4 + (0.1*m6.AddMatrix(m7)).AddMatrix(m7) ;
  	//std::cerr << "--- m8 ---" << std::endl << m8 ;
  
  m8.WriteMatrix();
  
  return 0;
}
