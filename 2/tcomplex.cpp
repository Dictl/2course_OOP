#include "tcomplex.h"

TComplex::TComplex() {
    real = 0;
    imaginary = 0;
}
TComplex::TComplex(double real_t): TComplex() {
    real = real_t;
    imaginary = 0;
    };
TComplex::TComplex(double real_t, double imaginary_t): TComplex() {
    real = real_t;
    imaginary = imaginary_t;
}
std::istream& operator>>(std::istream& stream, TComplex& tcomplex){
    double real;
    char sign;
    double imaginary;
    char ending;
<<<<<<< Updated upstream

=======
    std::cout<<"¬ведите каждый новый символ с новой строки, формат:(0+0i)"<<std::endl;
>>>>>>> Stashed changes
    if (stream >> real >> sign >> imaginary >> ending && (sign == '+' || sign == '-') && ending == 'i'){
        sign == '+' ?  tcomplex = TComplex(real, imaginary) : tcomplex = TComplex(real, -imaginary);
    }
    else{
        stream.setstate(std::ios_base::failbit);
    }
    return stream;
}
std::ostream& operator<<(std::ostream& stream, const TComplex& tcomplex){
    if (tcomplex.imaginary>=0)
    {
        stream<<tcomplex.real<<"+"<<tcomplex.imaginary<<"i";
    }
    else
    {
        stream<<tcomplex.real<<tcomplex.imaginary<<"i";
    }
    return stream;
}
TComplex::~TComplex(){}
TComplex sqrt(const TComplex& tcomplex)
{
    return tcomplex.sqrt_t();
}
