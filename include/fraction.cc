#include "fraction.h"
#include <valarray>

inline int gcd(int a, int b) {
    if (a < b)
        std::swap(a, b);
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return std::max(a, 1);
}

inline int get_digit(int a) {
    int res = 0;
    while (a) {
        a /= 10;
        res++;
    }
    return res;
}

void Fraction::Reduce() {
    int sign = 0;
    if (denominator == 0) {
        std::cerr << "\nError: the divisor is zero.\n";
        exit(-1);
    }
    if (numerator < 0) {
        numerator = -numerator;
        sign ^= 1;
    }
    if (denominator < 0) {
        denominator = -denominator;
        sign ^= 1;
    }
    int gcdnum = gcd(numerator, denominator);
    numerator /= gcdnum;
    denominator /= gcdnum;
    if (sign)
        numerator = -numerator;
}

Fraction::Fraction(double num) {
    while (num != (double)((int)num)) {
        denominator *= 10.0;
        num *= 10.0;
    }
    numerator = num;
    Reduce();
}

Fraction Fraction::operator+(const Fraction &x) {
    Fraction result = 0;
    result.numerator = numerator * x.denominator + x.numerator * denominator;
    result.denominator = denominator * x.denominator;
    result.Reduce();
    return result;
}

Fraction Fraction::operator-(const Fraction &x) {
    Fraction result = 0;
    result.numerator = numerator * x.denominator - x.numerator * denominator;
    result.denominator = denominator * x.denominator;
    result.Reduce();
    return result;
}

Fraction Fraction::operator*(const Fraction &x) {
    Fraction result = 0;
    result.numerator = numerator * x.numerator;
    result.denominator = denominator * x.denominator;
    result.Reduce();
    return result;
}

Fraction Fraction::operator/(const Fraction &x) {
    Fraction result = 0;
    result.numerator = numerator * x.denominator;
    result.denominator = denominator * x.numerator;
    result.Reduce();
    return result;
}

std::ostream &operator<<(std::ostream &out, const Fraction &x) {
    Fraction res = x;
    res.Reduce();
    if (res.denominator == 1) {
        out << res.numerator;
        output_len = get_digit(res.numerator);
    } else {
        out << "\\frac{" << res.numerator << "}{" << res.denominator << "}";
        output_len = get_digit(res.numerator) + 1 + get_digit(res.denominator);
    }
    if (res.numerator < 0)
        output_len++;
    return out;
}

std::istream &operator>>(std::istream &in, Fraction &x) {
    char s[20];
    in >> s;
    int sgn = 1, pos = -1, len = strlen(s);
    if (s[0] == '-') {
        sgn = -1;
        for (int i = 0; i < len - 1; i++)
            s[i] = s[i + 1];
        len--;
    }
    for (int i = 0; i < len; i++)
        if (s[i] == '/')
            pos = i;
    if (pos == -1) {
        int num1 = 0;
        int dotflag = 0;
        for (int i = 0; i < len; i++) {
            if (s[i] == '.') {
                dotflag = i;
                break;
            }
            num1 = num1 * 10 + s[i] - '0';
        }
        if (!dotflag)
            x = num1;
        else {
            double num2 = num1, num3 = 1;
            for (int i = dotflag + 1; i < len; i++) {
                num3 /= 10.0;
                num2 += (double)(s[i] - '0') / num3;
            }
            x = num2;
        }
    } else {
        int num1 = 0, num2 = 0;
        for (int i = 0; i < pos; i++)
            num1 = num1 * 10 + s[i] - '0';
        for (int i = pos + 1; i < len; i++)
            num2 = num2 * 10 + s[i] - '0';
        x.numerator = num1;
        x.denominator = num2;
    }
    if (sgn == -1)
        x.numerator = -x.numerator;
    return in;
}
