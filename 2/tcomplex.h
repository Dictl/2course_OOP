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
    double magnitude () const{
        return ((this->real*this->real)+(this->imaginary*this->imaginary));
    };
    TComplex sqrt_t() const
    {
        if (imaginary != 0) {
            return TComplex(sqrt((sqrt(real*real + imaginary*imaginary) + real)/2),
                            imaginary/fabs(imaginary)*sqrt((sqrt(real*real + imaginary*imaginary) - real)/2));
        }
        else{
            return TComplex(sqrt(real),0);
        }
    }
    TComplex operator+(const TComplex& tcomplex) const{
        return TComplex(real+tcomplex.real, imaginary+tcomplex.imaginary);
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
    bool operator>(const TComplex& tcomplex) const{
        if(this->magnitude() > tcomplex.magnitude()){
            return true;
        }
        else{
            return false;
        }
    }
    bool operator<(const TComplex& tcomplex) const{
        if(this->magnitude() < tcomplex.magnitude()){
            return true;
        }
        else{
            return false;
        }
    }



private:
    double real, imaginary;
};

TComplex sqrt(const TComplex& tcomplex);

#endif // TCOMPLEX_H
