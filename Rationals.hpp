#ifndef RATIONALS_HPP
#define RATIONALS_HPP
#include <iostream>
#include <cstddef>
#include <cmath>
#include <random>

const long long int INF = 10000000;

class Rational
{
    private:
        long long int numerator;
        long long int denomenator;
    public:
        Rational();
        Rational(int a);
        Rational(const long long int a, const long long int b);
        Rational(const Rational &other);

        Rational Simplify();

        Rational operator+(const Rational &other) const;
        Rational operator-(const Rational &other) const;
        Rational operator-() const;
        Rational operator*(const Rational &other) const;
        Rational operator*(const long long int &other) const;
        Rational operator/(const Rational &other) const;
        
        Rational& operator=(const Rational &other);
        
        bool operator<(const Rational &other) const {return (this->numerator * other.denomenator) < (this->denomenator * other.numerator);};
        bool operator>(const Rational &other) const {return (this->numerator * other.denomenator) > (this->denomenator * other.numerator);};
        bool operator==(const Rational &other) const {return (this->numerator * other.denomenator) == (this->denomenator * other.numerator);};

        bool isNaN() const {return denomenator;};
        
        Rational operator++(int);
        Rational& operator++();
        Rational operator--(int);
        Rational& operator--();

        template<typename T>
        Rational& operator+=(const T &other)
        {
            *this = *this + other;
            return *this;
        }

        template<typename T>
        Rational& operator-=(const T &other)
        {
            *this = *this - other;
            return *this;
        }
        
        template<typename T>
        Rational& operator*=(const T &other)
        {
            *this = *this * other;
            return *this;
        }

        template<typename T>
        Rational& operator/=(const T &other)
        {
            *this = *this / other;
            return *this;
        }

        explicit operator int() const {return numerator / denomenator;};
        operator double() const {return static_cast<double>(numerator) / denomenator;};

        friend std::ostream& operator<<(std::ostream &out, const Rational &R);
};


namespace Rationals
{
    size_t recursiveGCD(size_t n, size_t k);

    long long int binaryGCD(long long int n, long long int k);
    
    template<typename Rational> Rational Random()
    {
        static std::random_device r;  
        static std::default_random_engine e1(r());  
        static std::uniform_int_distribution<long long int> uniform_dist(-INF, INF);  
        Rational result(uniform_dist(e1), uniform_dist(e1));  
        return result;                                            
    }
}
#endif
