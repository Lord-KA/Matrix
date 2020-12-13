#include "Rationals.hpp"


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
    (*this).Simplify();
}


bool Rational::isNaN() const
{
    return denomenator;
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
    return result;
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
    out << R.numerator << '/' << R.denomenator;
    return out;
}
