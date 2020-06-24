#include "rational.hpp"
#include <exception>
#include <stdexcept>
#include <iostream>

int helper_funcs::gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

rational::rational(int p, int q)
        :p_(p)
        ,q_(q)
    {
        if (q == 0)
            throw std::domain_error("Zero Denominator");

        simplify();
    }

rational::rational()
    :p_(0)
    ,q_(1)
{}

rational::rational(const rational& other)
    :p_(other.p_)
    ,q_(other.q_)
{}

rational rational::inverse() const
{
    return rational(q_, p_);
}

rational& rational::operator=(const rational& other) = default;

rational& rational::operator+=(const rational& other)
{
    p_ = p_ * other.q_ + q_ * other.p_;
    q_ *= other.q_;
    simplify();

    return *this;
}

rational rational::operator+(const rational& other) const
{
    return rational(*this) += other;

}

rational& rational::operator-=(const rational& other)
{
    p_ = p_ * other.q_ - q_ * other.p_;
    q_ *= other.q_;
    simplify();

    return *this;
}

rational rational::operator-(const rational& other) const
{
    return rational(*this) -= other;
}

rational& rational::operator*=(const rational& other)
{
    p_ *= other.p_;
    q_ *= other.q_;
    simplify();

    return *this;
}

rational rational::operator*(const rational& other) const
{
    return rational(*this) *= other;
}

rational& rational::operator/=(const rational& other)
{
    if (other.p_ == 0)
        throw std::domain_error("Division by zero not allowed");

    return *this *= other.inverse();
}

rational rational::operator/(const rational& other) const
{
    return rational(*this) /= other;
}

bool rational::operator<(const rational& other) const
{
    return p_ * other.q_  <  q_ * other.p_;
}

bool rational::operator==(const rational& other) const
{
    if (p_ == 0)
        return p_ == other.p_;

    return p_ == other.p_ && q_ == other.q_;
}

bool rational::operator<=(const rational& other) const
{
    return  *this < other || *this == other;
}

bool rational::operator>=(const rational& other) const
{
    return !(*this < other);
}

bool rational::operator>(const rational& other) const
{
    return !(*this<=other);
}

void rational::simplify()
{
    if (q_ < 0)
    {
        p_ = -p_;
        q_ = -q_;
    }

    int gcd = helper_funcs::gcd(p_, q_);
    p_ /= gcd;
    q_ /= gcd;

}

int rational::get_numerator() const
{
    return p_;
}

int rational::get_denominator() const
{
    return q_;
}

std::ostream& operator<<(std::ostream& os, const rational& r)
{
    os << r.get_numerator() << '/' << r.get_denominator();
    return os;
}
