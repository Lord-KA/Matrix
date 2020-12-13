#ifndef RATIONALS_HPP
#define RATIONALS_HPP
#include <iostream>
#include <cstddef>


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
        Rational operator/(const Rational &other) const;
        
        Rational& operator=(const Rational &other);
        
        bool operator<(const Rational &other) const {return (this->numerator * other.denomenator) < (this->denomenator * other.numerator);};
        bool operator>(const Rational &other) const {return (this->numerator * other.denomenator) > (this->denomenator * other.numerator);};
        bool operator==(const Rational &other) const {return (this->numerator * other.denomenator) == (this->denomenator * other.numerator);};

        bool isNaN() const;
        
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
        
        //static operator int(Rational other);
        operator int() const {return numerator / denomenator;};
        operator double() const {return (double)numerator / (double)denomenator;};

        friend std::ostream& operator<<(std::ostream &out, const Rational &R);
};

#endif
