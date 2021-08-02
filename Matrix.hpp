#ifndef MATRIX_h
#define MATRIX_h

#include <iostream>
#include <cassert>
#include <random>
#include <utility>


#ifndef NTHREADS
#include "pthread.h"

static size_t threadNum = 1;
#endif

static int randomDispersion = 1e2;


template<typename T> //DEBUG
class SPMatrix;

template<typename T>
class Matrix
{
    friend SPMatrix<T>;     //DEBUG
    private:

        size_t rows;
        size_t cols;
        T determinant;
        bool determinantIsNaN;

        T *matrix;
        
    public:
        Matrix( size_t rows = 0, size_t cols = 0, T val = 0 );
        Matrix( const Matrix & other );
        Matrix( Matrix&& other );

        ~Matrix();

        void WriteMatrix() const;
        void ReadMatrix ();

        void FillMatrixRandom( T (*CustomRandom)() );   
        void FillMatrixRandom();                        

        T CalcDeterminant();
        Matrix GaussianMethod() const;
        void swapRows( size_t i, size_t j );
        T MinorsMethod() const;
        Matrix Minor ( size_t i, size_t j ) const;

        Matrix Transposition() const;

        Matrix  operator+( const Matrix & other ) const;
        Matrix  operator-( const Matrix & other ) const;
        Matrix  operator-() const;
        Matrix  operator*( const Matrix & other ) const;
        Matrix  operator*( const T &n ) const;
        Matrix& operator=( const Matrix & other );
        Matrix& operator=( Matrix&& other );
        
        inline const T& operator() ( const size_t i, const size_t j ) const;  
        inline T& operator() ( size_t i, size_t j ); 

    friend std::ostream& operator<<( std::ostream &out, const Matrix &a )
    {    
        for(size_t i=0; i < a.rows; ++i){
            for(size_t j=0; j < a.cols; ++j)
                out << a(i, j) << ' ';
            out << '\n';
        }
        out << "\n";
        return out;
    }

    friend inline Matrix operator*( const T &n, const Matrix &M )
    {
        return M * n;
    }

    #ifndef NTHREADS 

    private:
        struct threadArgs;
        static void* multiplicationThread( void* inp );
        static void*       additionThread( void* inp );
        static void*    subtractionThread( void* inp );
        static void*      multConstThread( void* inp );
        static void*     assignmentThread( void* inp );
        static void*      assignValThread( void* inp );
        static void*     fillRandomThread( void* inp );
   
    #endif
};


#ifndef NTHREADS 

template<typename T>
struct Matrix<T>::threadArgs
{
    size_t beg, end;
    const T* val;
    const Matrix* this_;
    const Matrix* other_;
    Matrix* result_;
    T (*random_)();



    threadArgs() : beg(0), end(0), val(nullptr), this_(nullptr), other_(nullptr), result_(nullptr) {}

    threadArgs(size_t beg, size_t end, const Matrix* this_, const Matrix* other_, Matrix* result_, T (*random_)() = nullptr)
        : beg(beg), end(end), this_(this_), other_(other_), result_(result_), random_(random_) {}

    threadArgs(size_t beg, size_t end, const T* val, const Matrix* this_, const Matrix* other_, Matrix* result_)
        : beg(beg), end(end), val(val), this_(this_), other_(other_), result_(result_) {}

    threadArgs& operator=(const threadArgs& other)
    {
        beg = other.beg;
        end = other.end;
        val = other.val;
        this_ = other.this_;
        other_ = other.other_;
        result_ = other.result_;
        random_ = other.random_;

        return *this;
    }
};


template<typename T>
void* Matrix<T>::multiplicationThread(void* inp)
{
    threadArgs* args = static_cast<threadArgs*>(inp);
    size_t lim_i = std::min(args->end, args->this_->rows);

    for(size_t i=args->beg; i < lim_i; ++i)
        for(size_t j=0; j < args->other_->cols; ++j)
            for(size_t r=0; r < args->this_->cols; ++r)
                (*args->result_)(i, j) += (*args->this_)(i, r) * (*args->other_)(r, j);           

    return nullptr;
}

template<typename T>
void* Matrix<T>::additionThread(void* inp)
{
    threadArgs* args = static_cast<threadArgs*>(inp);
    size_t lim_j = std::min(args->end, args->this_->rows * args->this_->cols);

    for(size_t j=args->beg; j < lim_j; ++j)
        args->result_->matrix[j] = args->this_->matrix[j] + args->other_->matrix[j];           

    return nullptr;
}

template<typename T>
void* Matrix<T>::subtractionThread(void* inp)
{
    threadArgs* args = static_cast<threadArgs*>(inp);
    size_t lim_j = std::min(args->end, args->this_->rows * args->this_->cols);

    for(size_t j=args->beg; j < lim_j; ++j)
        args->result_->matrix[j] = args->this_->matrix[j] - args->other_->matrix[j];           

    return nullptr;
}

template<typename T>
void* Matrix<T>::multConstThread(void* inp)
{
    threadArgs* args = static_cast<threadArgs*>(inp);
    size_t lim_j = std::min(args->end, args->this_->rows * args->this_->cols);

    for(size_t j=args->beg; j < lim_j; ++j)
        args->result_->matrix[j] = args->this_->matrix[j] * *args->val;

    return nullptr;
}

template<typename T>
void* Matrix<T>::assignmentThread(void* inp)
{
    threadArgs* args = static_cast<threadArgs*>(inp);
    size_t lim_j = std::min(args->end, args->this_->rows * args->this_->cols);
    
    std::copy(&args->other_->matrix[args->beg], &args->other_->matrix[lim_j], &args->this_->matrix[args->beg]);

    return nullptr;
}


template<typename T>
void* Matrix<T>::assignValThread(void* inp)
{
    threadArgs* args = static_cast<threadArgs*>(inp);
    size_t lim_j = std::max(args->beg, std::min(args->end, args->this_->rows * args->this_->cols));

    std::fill(&args->this_->matrix[args->beg], &args->this_->matrix[lim_j], *args->val);

    return nullptr;
}

template<typename T>
void* Matrix<T>::fillRandomThread(void* inp)
{
    threadArgs* args = static_cast<threadArgs*>(inp);
    size_t lim_j = std::min(args->end, args->this_->rows * args->this_->cols);

    for(size_t j=args->beg; j < lim_j; ++j)
        args->this_->matrix[j] = args->random_();           

    return nullptr;
}

#endif 

template<typename T>
const T& Matrix<T>::operator() (const size_t i, const size_t j) const
{
    assert(i < rows && j < cols);
    return matrix[i * cols + j];
}

template<typename T>
T& Matrix<T>::operator() (const size_t i, const size_t j)
{
    assert(i < rows && j < cols);
    return matrix[i * cols + j];
}


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const
#ifndef NTHREADS
{
    assert(rows == other.rows && cols == other.cols);
    
    Matrix result = Matrix(other);
    size_t lim_i = rows * cols;
    size_t split = lim_i / threadNum + 1;

    pthread_t thrd_ids[threadNum];
    threadArgs args[threadNum];
    size_t thrdN;
    for (thrdN = 0; thrdN < threadNum; ++thrdN){
        args[thrdN] = threadArgs(thrdN * split, (thrdN + 1) * split, this, &other, &result);
        pthread_create(&thrd_ids[thrdN], nullptr, additionThread, &args[thrdN]);
    }

    for (size_t i=0; i < thrdN; ++i)
        pthread_join(thrd_ids[i], nullptr);

    return result; 
}
#else
{
    assert(rows == other.rows && cols == other.cols);
    
    Matrix result = Matrix(other);
    for(size_t i=0; i < rows * cols; ++i)
        result.matrix[i] += matrix[i];

    return result; 
}
#endif

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const
#ifndef NTHREADS
{
    assert(rows == other.rows && cols == other.cols);
    
    Matrix result = Matrix(other);
    size_t lim_i = rows * cols;
    size_t split = lim_i / threadNum + 1;

    pthread_t thrd_ids[threadNum];
    threadArgs args[threadNum];
    size_t thrdN;
    for (thrdN = 0; thrdN < threadNum; ++thrdN){
        args[thrdN] = threadArgs(thrdN * split, (thrdN + 1) * split, this, &other, &result);
        pthread_create(&thrd_ids[thrdN], nullptr, subtractionThread, &args[thrdN]);
    }


    for (size_t i=0; i < thrdN; ++i)
        pthread_join(thrd_ids[i], nullptr);
    

    return result; 
}
#else
{
    assert(rows == other.rows && cols == other.cols);
    
    Matrix result = Matrix(*this);
    for(size_t i=0; i < rows * cols; ++i)
        result.matrix[i] -= other.matrix[i];

    return result; 
}
#endif

template<typename T>
Matrix<T> Matrix<T>::operator-() const
{
    return -1 * (*this);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const
#ifndef NTHREADS
{
    assert(cols == other.rows);
    
    Matrix result(rows, other.cols);
    size_t split = rows / threadNum + 1;

    pthread_t thrd_ids[threadNum];
    threadArgs args[threadNum];
    size_t thrdN;

    for (thrdN = 0; thrdN < threadNum; ++thrdN){
        args[thrdN] = threadArgs(thrdN * split, (thrdN + 1) * split, this, &other, &result);
        pthread_create(&thrd_ids[thrdN], nullptr, multiplicationThread, &args[thrdN]);
    }

    for (size_t i=0; i < thrdN; ++i)
        pthread_join(thrd_ids[i], nullptr);   

    return result;
}

#else
{
    assert(cols == other.rows);
 
    Matrix result(rows, other.cols);

    for(size_t i=0; i < rows; ++i)
        for(size_t j=0; j < other.cols; ++j){
            T sum = 0;
            for(size_t r=0; r < cols; ++r)          
                sum += (*this)(i, r) * other(r, j);
            result(i, j) = sum;
        }

    return result;
}
#endif

template<typename T>
Matrix<T> Matrix<T>::operator*(const T &n) const
#ifndef NTHREADS
{
    Matrix result = Matrix(rows, cols);

    size_t lim_i = rows * cols;
    size_t split = lim_i / threadNum + 1;

    pthread_t thrd_ids[threadNum];
    threadArgs args[threadNum];
    size_t thrdN;

    for (thrdN = 0; thrdN < threadNum; ++thrdN){
        args[thrdN] = threadArgs(thrdN * split, (thrdN + 1) * split, &n, this, nullptr, &result);
        pthread_create(&thrd_ids[thrdN], nullptr, multConstThread, &args[thrdN]);
    }

    for (size_t i=0; i < thrdN; ++i)
        pthread_join(thrd_ids[i], nullptr);

    return result; 
}
#else
{
    Matrix result = Matrix(rows, cols);

    for(size_t i=0; i < rows * cols; ++i)
        result.matrix[i] = matrix[i] * n;

    return result;
}
#endif


template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other)
{
    if(this == &other)
        return *this;
    
    delete[] matrix;

    matrix = std::exchange(other.matrix, nullptr);
    rows   = std::exchange(other.rows, 0);
    cols   = std::exchange(other.cols, 0);

    determinant      = other.determinant;
    determinantIsNaN = other.determinantIsNaN;

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &other)
{
    if (this == &other)
        return *this;

    rows = other.rows;
    cols = other.cols;

    determinant = other.determinant;
    determinantIsNaN = other.determinantIsNaN;

    T *temp = matrix;

    matrix = new T[rows * cols];

    size_t lim_i = rows * cols;

    #ifndef NTHREADS
    size_t split = lim_i / threadNum + 1;

    pthread_t thrd_ids[threadNum];
    threadArgs args[threadNum];
    size_t thrdN;
            
    for (thrdN = 0; thrdN < threadNum; ++thrdN){   
        args[thrdN] = threadArgs(thrdN * split, (thrdN + 1) * split, this, &other, nullptr);
        pthread_create(&thrd_ids[thrdN], nullptr, assignmentThread, &args[thrdN]);
    }
        
    for (size_t i=0; i < thrdN; ++i)
        pthread_join(thrd_ids[i], nullptr);
    
    #else
    for(size_t i=0; i < lim_i; ++i)
        matrix[i] = other.matrix[i];
    #endif

    delete[] temp;

    return *this;
}


template<typename T>
Matrix<T>::~Matrix()
{
    //delete[] matrix;

    matrix = nullptr;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other)
{
    rows = other.rows;
    cols = other.cols;
    determinant = other.determinant;
    determinantIsNaN = other.determinantIsNaN;

    matrix = new T[rows * cols];

    size_t lim_i = rows * cols;
        
    #ifndef NTHREADS
    size_t split = lim_i / threadNum + 1;

    pthread_t thrd_ids[threadNum];
    threadArgs args[threadNum];
    size_t thrdN;
                                                                        
    for (thrdN = 0; thrdN < threadNum; ++thrdN){
        args[thrdN] = threadArgs(thrdN * split, (thrdN + 1) * split, this, &other, nullptr);
        pthread_create(&thrd_ids[thrdN], nullptr, assignmentThread, &args[thrdN]);
    }
            
    for (size_t i=0; i < thrdN; ++i)
        pthread_join(thrd_ids[i], nullptr);
    
    #else
    for(size_t i=0; i < lim_i; ++i)
        matrix[i] = other.matrix[i];
    #endif
}

template<typename T>
Matrix<T>::Matrix(Matrix&& other)
{
    matrix = std::exchange(other.matrix, nullptr);
    rows   = std::exchange(other.rows, 0);
    cols   = std::exchange(other.cols, 0);
    determinant      = std::exchange(other.determinant, 0);
    determinantIsNaN = std::exchange(other.determinantIsNaN, true);
}

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, T val)
    : rows(r), cols(c), determinant(0), determinantIsNaN(true)
{
    matrix = new T[rows * cols];

    size_t lim_i = rows * cols;

    #ifndef NTHREADS
    size_t split = lim_i / threadNum + 1;

    pthread_t thrd_ids[threadNum];
    threadArgs args[threadNum];
    size_t thrdN;
    
    for (thrdN = 0; thrdN < threadNum; ++thrdN){
        args[thrdN] = threadArgs(thrdN * split, (thrdN + 1) * split, &val, this, nullptr, nullptr);
        pthread_create(&thrd_ids[thrdN], nullptr, assignValThread, &args[thrdN]);
    }

    for (size_t i=0; i < thrdN; ++i)
        pthread_join(thrd_ids[i], nullptr);
       
    #else
    for(size_t i=0; i < lim_i; ++i)
        matrix[i] = 0;
    #endif
}


template<typename T>
Matrix<T> Matrix<T>::Transposition() const
{
    Matrix result = Matrix(cols, rows);

    for(size_t i=0; i < rows; ++i)
        for(size_t j=0; j < cols; ++j)
            result(j, i) = (*this)(i, j); 

    return result;
}


template<typename T>
T Matrix<T>::CalcDeterminant()
{
    if (!determinantIsNaN)
        return determinant;
    
    if (rows != cols) 
        return MinorsMethod();
    

    determinant = 1;
    determinantIsNaN = false;
    Matrix Triangular = GaussianMethod();
    if (Triangular.matrix == nullptr){
        determinant = MinorsMethod();
        return determinant;
    }
    for(size_t i=0; i < rows; ++i)
        determinant *= Triangular(i, i);

    return determinant;
}

template<typename T>
Matrix<T> Matrix<T>::GaussianMethod() const
{
    Matrix result = Matrix(*this);
    int determinant_ratio = 1;
    for(size_t k=0; k < rows; ++k)
    {
        if (result(k, k) == T(0)){
            size_t i = k + 1;
            while (i < cols && result(k, i) == T(0))
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
            }
        }
    }
    return result * determinant_ratio;
}

template<typename T>
void Matrix<T>::swapRows(size_t row_1, size_t row_2)
{
    for(size_t i=0; i<cols; ++i){
        T temp = (*this)(row_1, i);
        (*this)(row_1, i) = (*this)(row_2, i);
        (*this)(row_2, i) = temp;
    }
}

template<typename T>
T Matrix<T>::MinorsMethod() const
{
    T result = 0;
    if (rows==2 && cols==2) 
        return (*this)(0,0) * (*this)(1,1) - (*this)(0, 1) * (*this)(1, 0);

    for(size_t i=0; i < rows; ++i){
        result += (*this)(0, i) * T(i%2==0?1:-1) * Minor(0, i).MinorsMethod();
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::Minor(size_t i, size_t j) const
{
    Matrix result(rows-1, cols-1);
    bool flag_row = false;          // flag for skipping r == i

    for(size_t r=0; r<rows-1; ++r){
        bool flag_col = false;      // flag for skipping c = j every r

        for(size_t c=0; c<cols-1; ++c){
            if (r == i) flag_row = true;
            if (c == j) flag_col = true;
        
            result(r, c) = (*this)(r + flag_row, c + flag_col);
        }
    }

    return result;
}


template<typename T>
T Random()
{
    static std::random_device r;
    static std::default_random_engine e1(r());
    std::uniform_int_distribution<T> uniform_dist(-randomDispersion, randomDispersion);

    return uniform_dist(e1);
}

template<>
double Random()
{
    static std::random_device r;
    static std::default_random_engine e1(r());
    static std::uniform_real_distribution<double> uniform_dist(-randomDispersion, randomDispersion);

    return uniform_dist(e1);
}

#ifndef NTHREADS
void setThreadNum(size_t n)
{
    threadNum = n;
}

size_t getThreadNum()
{
    return threadNum;
}
#endif
 

template<typename T>
void Matrix<T>::FillMatrixRandom(T (*CustomRandom)())
#ifndef NTHREADS
{
    size_t lim_i = rows * cols;
    size_t split = lim_i / threadNum + 1;

    pthread_t thrd_ids[threadNum];
    threadArgs args[threadNum];
    size_t thrdN;
    
    for (thrdN = 0; thrdN < threadNum; ++thrdN){
        args[thrdN] = threadArgs(thrdN * split, (thrdN + 1) * split, this, nullptr, nullptr, &CustomRandom);
        pthread_create(&thrd_ids[thrdN], nullptr, fillRandomThread, &args[thrdN]);
    }

    for (size_t i=0; i < thrdN; ++i)
        pthread_join(thrd_ids[i], nullptr);
}
#else
{
    for(size_t i = 0; i < rows; ++i)
        for(size_t j = 0; j < cols; ++j)
            (*this)(i, j) = (*CustomRandom)(); 
}
#endif

template<typename T>
void Matrix<T>::FillMatrixRandom()
#ifndef NTHREADS
{
    size_t lim_i = rows * cols;
    size_t split = lim_i / threadNum + 1;

    pthread_t thrd_ids[threadNum];
    threadArgs args[threadNum];
    size_t thrdN;
    
    for (thrdN = 0; thrdN < threadNum; ++thrdN){
        args[thrdN] = threadArgs(thrdN * split, (thrdN + 1) * split, this, nullptr, nullptr, &Random<T>);
        pthread_create(&thrd_ids[thrdN], nullptr, fillRandomThread, &args[thrdN]);
    }

    for (size_t i=0; i < thrdN; ++i)
        pthread_join(thrd_ids[i], nullptr);

}
#else
{
   for(size_t i = 0; i < rows; ++i)
        for(size_t j = 0; j < cols; ++j)
            (*this)(i, j) = Random<T>(); 
}
#endif


template<typename T>
void Matrix<T>::WriteMatrix() const
{
    std::cout << rows << ' ' << cols << std::endl;

    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j)
            std::cout << (*this)(i, j) << ' '; 
        std::cout << std::endl;
    }
}


template<typename T>
void Matrix<T>::ReadMatrix()
{
    size_t r, c;
    std::cin >> r >> c;
    if (r * c != rows * cols)
    {
        delete[] matrix;
        matrix = new T[rows * cols];
        rows = r;
        cols = c;
    }

    for(size_t i=0; i<rows; ++i)
        for(size_t j=0; j<cols; ++j)
            std::cin >> (*this)(i, j);
}


#endif
