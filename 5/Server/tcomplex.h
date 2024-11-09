#pragma once
#ifndef TCOMPLEX_H
#define TCOMPLEX_H
#include <iostream>
class TComplex{

public:
    TComplex();
    TComplex(double real_t);
    TComplex(double real_t, double imaginary_t);
    ~TComplex();
    friend std::istream& operator>>(std::istream& stream, TComplex& tcomplex);
    friend std::ostream& operator<<(std::ostream& stream, const TComplex& tcomplex);
    bool operator==(const TComplex& tcomplex) const;
    bool operator!=(const TComplex& tcomplex) const;
    bool operator>(const TComplex& tcomplex) const;
    bool operator<(const TComplex& tcomplex) const;
    TComplex operator+(const TComplex& tcomplex) const;
    TComplex operator-(const TComplex& tcomplex) const;
    TComplex operator*(const double tdouble) const;
    TComplex operator*(const int tint) const;
    TComplex operator*(const TComplex& tcomplex) const;
    TComplex operator/(const double tdouble) const;
    TComplex operator/(const int tint) const;
    TComplex operator/(const TComplex& tcomplex) const;
    double get_real() const;
    double get_image() const;
    double magnitude() const;
    TComplex sqrt_t() const;
    TComplex pow_t(int y) const;
private:
    double real, imaginary;
};

TComplex sqrt(const TComplex& tcomplex);
TComplex pow(const TComplex& tcomplex, int y);

#endif // TCOMPLEX_H
