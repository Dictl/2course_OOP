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
    stream >> real >> sign >> imaginary >> ending; // input from terminal is ALWAYS in complex form
    if ((sign == '+' || sign == '-') && ending == 'i'){
        if (imaginary != 0) {
            sign == '+' ?  tcomplex = TComplex(real, imaginary) : tcomplex = TComplex(real, -imaginary);
        }
        else {
            tcomplex = TComplex(real); // if imaginary part is EXPLICITLY ZERO: example: 1+0i
        }
    }
    else {
        stream.setstate(std::ios_base::failbit);
    }
    return stream;
}
std::ostream& operator<<(std::ostream& stream, const TComplex& tcomplex){

    if (tcomplex.imaginary>0)
    {
        stream << tcomplex.real<<"+"<<tcomplex.imaginary<<"i" << ")";
    }
    else if (tcomplex.imaginary==0){
        stream<<tcomplex.real;
    }
    else
    {
        stream<<tcomplex.real<<tcomplex.imaginary<<"i"<< ")";
    }

    return stream;
}
TComplex::~TComplex(){

}
TComplex TComplex::sqrt_t() const{
    if (imaginary != 0) {
        return TComplex(sqrt((sqrt(real*real + imaginary*imaginary) + real)/2),
                        imaginary/fabs(imaginary)*sqrt((sqrt(real*real + imaginary*imaginary) - real)/2));
    }
    else{
        return TComplex(sqrt(real),0);
    }
}
TComplex sqrt(const TComplex& tcomplex){
    return tcomplex.sqrt_t();
}
TComplex TComplex::pow_t(int y) const{
    bool negative;
    y >= 0 ? negative = false : negative = true;
    TComplex result = *this;
    if (y == 1){
        return result;
    }
    if (y == 0){
        return TComplex();
    }
    for (int i = 0; i < y-1; i++){
        result = result * *this;
    }
    if(negative){
        return TComplex(1)/result;
    }
    else{
        return result;
    }
};
TComplex pow(const TComplex& tcomplex, int y){
    return tcomplex.pow_t(y);
}
double TComplex::get_real() const {
    return real;
}
double TComplex::get_image() const{
    return imaginary;
}
