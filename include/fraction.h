#include <iostream>
#include <string.h>

#ifdef _WIN32
#define CONSOLE "CON"
#elif __linux__
#define CONSOLE "/dev/tty"
#endif

extern int output_len;

class Fraction {
  private:
    int numerator, denominator;
    void Reduce();

  public:
    Fraction(int num = 0) : numerator(num), denominator(1) {}
    Fraction(int num, int deno) : numerator(num), denominator(deno) { Reduce(); }
    Fraction(const Fraction &x) : numerator(x.numerator), denominator(x.denominator) { Reduce(); }
    Fraction(double num);

    Fraction operator+(const Fraction &x);
    Fraction operator-(const Fraction &x);
    Fraction operator*(const Fraction &x);
    Fraction operator/(const Fraction &x);

    bool operator==(const Fraction &y) {
        Fraction x1 = *this, y1 = y;
        x1.Reduce();
        y1.Reduce();
        if (x1.numerator == y1.numerator && x1.denominator == y1.denominator)
            return 1;
        return 0;
    }

    friend std::ostream &operator<<(std::ostream &out, const Fraction &x);
    friend std::istream &operator>>(std::istream &in, Fraction &x);
};