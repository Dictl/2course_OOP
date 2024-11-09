#pragma once
#ifndef TCOMPLEX_H
#define TCOMPLEX_H
#include <iostream>
#include <cmath>
class TComplex{

public:
    TComplex();
    TComplex(double real_t);
    TComplex(double real_t, double imaginary_t);
    ~TComplex();
    friend std::istream& operator>>(std::istream& stream, TComplex& tcomplex);
    friend std::ostream& operator<<(std::ostream& stream, const TComplex& tcomplex);
    double get_real() const;
    double get_image() const;
    double magnitude() const{
        return ((this->real*this->real)+(this->imaginary*this->imaginary));
    };
    TComplex sqrt_t() const;
    TComplex pow_t(int y) const;
    TComplex operator+(const TComplex& tcomplex) const{
        return TComplex(real+tcomplex.real, imaginary+tcomplex.imaginary);
    }
    bool operator==(const TComplex& tcomplex) const{
        return (this->real==tcomplex.real && this->imaginary==tcomplex.imaginary);
    }
    bool operator!=(const TComplex& tcomplex) const{
        return !(this->real==tcomplex.real && this->imaginary==tcomplex.imaginary);
    }
    TComplex operator-(const TComplex& tcomplex) const{
        return TComplex(real-tcomplex.real, imaginary-tcomplex.imaginary);
    }
    TComplex operator*(const double tdouble) const{
        return TComplex(real*tdouble, imaginary*tdouble);
    }
    TComplex operator*(const int tint) const{
        return TComplex(real*tint, imaginary*tint);
    }
    TComplex operator*(const TComplex& tcomplex) const{
        return TComplex((real*tcomplex.real-imaginary*
                                            tcomplex.imaginary), (real*tcomplex.imaginary+imaginary*tcomplex.real));
    }
    TComplex operator/(const double tdouble) const{
        return TComplex(real/tdouble, imaginary/tdouble);
    }
    TComplex operator/(const int tint) const{
        return TComplex(real/tint, imaginary/tint);
    }
    TComplex operator/(const TComplex& tcomplex) const{
        return TComplex(

                (this->real*tcomplex.real+this->imaginary*tcomplex.imaginary)
                /                                                             // real part
                (pow(tcomplex.real,2)+pow(tcomplex.imaginary,2))

                ,

                (this->imaginary*tcomplex.real-this->real*tcomplex.imaginary)
                /                                                             // imaginary part
                (pow(tcomplex.real,2)+pow(tcomplex.imaginary,2))

        );
    }
    bool operator>(const TComplex& tcomplex) const{
        return (this->magnitude() > tcomplex.magnitude());
    }
    bool operator<(const TComplex& tcomplex) const{
        return (this->magnitude() < tcomplex.magnitude());
    }
private:
    double real, imaginary;
};

TComplex sqrt(const TComplex& tcomplex);
TComplex pow(const TComplex& tcomplex, int y);

#endif // TCOMPLEX_H
