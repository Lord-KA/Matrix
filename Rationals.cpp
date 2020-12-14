#include "Rationals.hpp"

long long int abs(long long int n) {return (n<0)?-n:n;};

Rational::Rational()
{
    numerator = 0;
    denomenator = 0;
}

Rational::Rational(const long long int a, const long long int b)
{
    numerator = a;
    denomenator = b;
    (*this).Simplify();
}

Rational::Rational(const int a)
{
    numerator = a;
    denomenator = 1;
}

Rational::Rational(const Rational &other)
{
    numerator = other.numerator;
    denomenator = other.denomenator;
}


Rational Rational::operator+(const Rational &other) const
{
    Rational result(0);
    result.numerator = this->numerator * other.denomenator + this->denomenator * other.numerator;
    result.denomenator = this->denomenator * other.denomenator;
    return result.Simplify();
}

Rational Rational::operator-(const Rational &other) const
{
    Rational result((*this));
    return (result + -other);
}

Rational Rational::operator*(const Rational &other) const
{
    Rational result(other);
    result.numerator *= this->numerator;
    result.denomenator *= this->denomenator;
    return result.Simplify();
}

Rational Rational::operator*(const long long int &other) const
{
    Rational result(*this);
    result.numerator *= other;
    return result.Simplify();
}

Rational Rational::operator-() const
{
    Rational result = *this * Rational(-1);
    return result;
}

Rational Rational::operator/(const Rational &other) const
{
    Rational result(*this);
    result.numerator *= other.denomenator;
    result.denomenator *= other.numerator;
    return result.Simplify();
}


Rational Rational::operator++(int)
{
    Rational old(*this);
    (*this).numerator += (*this).denomenator;
    return old;

}

Rational& Rational::operator++()
{
    (*this).numerator += (*this).denomenator;
    return *this;
}

Rational Rational::operator--(int)
{
    Rational old(*this);
    (*this).numerator -= (*this).denomenator;
    return old;
}

Rational& Rational::operator--()
{
    (*this).numerator -= (*this).denomenator;
    return *this;
}


Rational& Rational::operator=(const Rational &other)
{
    (*this).numerator = other.numerator;
    (*this).denomenator = other.denomenator;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const Rational &R)
{
    if (R.denomenator == 1 || R.numerator == 0)
        out << R.numerator;
    else
       out << R.numerator << '/' << R.denomenator;
    return out;
}


long long int binaryGCD(long long int n, long long int k)
{
    if (n == 0) return k;
    if (k == 0) return n;

    size_t shift = __builtin_ctz(n | k);
    n >>= __builtin_ctz(n);

    do {
        k >>= __builtin_ctz(k);
        if (n > k){
            size_t temp = k;
            k = n;
            n = temp;
        }
        k -= n;
    } while (k > 0);
    return n << shift;   
}

size_t recurciveGCD(size_t n, size_t k)
{
    if (n == 0) return k;
    if (k == 0) return n;
    return recurciveGCD(k, n % k);
}


Rational Rational::Simplify()
{
    if (denomenator < 0)
    {
        denomenator *= -1;
        numerator *= -1;
    }
    long long int GCD;
    if (abs(denomenator) + abs(numerator) < 2000)
        GCD = binaryGCD(abs(denomenator), abs(numerator));
    else
        GCD = recurciveGCD(abs(denomenator), abs(numerator));
    this->numerator /= GCD;
    this->denomenator /=GCD;
    return (*this);
}
