#pragma once

#include <iosfwd>
namespace helper_funcs
{
    int gcd(int a, int b);
}

class rational
{
public:
    rational(int p, int q);

    rational();

    rational(const rational& other);

    rational inverse() const;

    rational& operator=(const rational& other);

    rational& operator+=(const rational& other);

    rational operator+(const rational& other) const;

    rational& operator-=(const rational& other);

    rational operator-(const rational& other) const;

    rational& operator*=(const rational& other);

    rational operator*(const rational& other) const;

    rational& operator/=(const rational& other);

    rational operator/(const rational& other) const;

    bool operator<(const rational& other) const;

    bool operator==(const rational& other) const;

    bool operator<=(const rational& other) const;

    bool operator>=(const rational& other) const;

    bool operator>(const rational& other) const;

    friend std::ostream& operator<< (std::ostream& os, const rational& r);

    int get_numerator() const;

    int get_denominator() const;

private:
    int p_;
    int q_;

    void simplify();
};

