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
TComplex::~TComplex(){

}
std::istream& operator>>(std::istream& stream, TComplex& tcomplex){
    std::string token;
    stream >> token;
    double real;
    double imaginary;

    std::regex complexRegex(R"((-?\d+(\.\d+)?)([+-]\d+(\.\d+)?)i)");
    std::smatch match;

    if (std::regex_match(token, match, complexRegex)) {
        real = std::stod(match[1].str());
        imaginary = std::stod(match[3].str());
        tcomplex = TComplex(real, imaginary);
    }
    else {
        try {
            real = std::stod(token);
            tcomplex = TComplex(real);
        } catch (...) {
            stream.setstate(std::ios_base::failbit);
            return stream;
        }
    }
    return stream;
}
std::ostream& operator<<(std::ostream& stream, const TComplex& tcomplex){

    if (tcomplex.imaginary>0)
    {
        stream << tcomplex.real<<"+"<<tcomplex.imaginary<<"i";
    }
    else if (tcomplex.imaginary==0){
        stream<<tcomplex.real;
    }
    else if (tcomplex.real!=0)
    {
        stream<<tcomplex.real<<tcomplex.imaginary<<"i";
    }
    else{
        stream<<tcomplex.imaginary<<"i";
    }
    return stream;
}
bool TComplex::operator==(const TComplex& tcomplex) const{
    return (this->real==tcomplex.real && this->imaginary==tcomplex.imaginary);
}
bool TComplex::operator!=(const TComplex& tcomplex) const{
    return !(this->real==tcomplex.real && this->imaginary==tcomplex.imaginary);
}
bool TComplex::operator>(const TComplex& tcomplex) const{
    return (this->magnitude() > tcomplex.magnitude());
}
bool TComplex::operator<(const TComplex& tcomplex) const{
    return (this->magnitude() < tcomplex.magnitude());
}
TComplex TComplex::operator+(const TComplex& tcomplex) const{
    return TComplex(real+tcomplex.real, imaginary+tcomplex.imaginary);
}
TComplex TComplex::operator-(const TComplex& tcomplex) const{
    return TComplex(real-tcomplex.real, imaginary-tcomplex.imaginary);
}
TComplex TComplex::operator*(const double tdouble) const{
    return TComplex(real*tdouble, imaginary*tdouble);
}
TComplex TComplex::operator*(const int tint) const{
    return TComplex(real*tint, imaginary*tint);
}
TComplex TComplex::operator*(const TComplex& tcomplex) const{
    return TComplex((real*tcomplex.real-imaginary*
    tcomplex.imaginary), (real*tcomplex.imaginary+imaginary*tcomplex.real));
}
TComplex TComplex::operator/(const double tdouble) const{
    return TComplex(real/tdouble, imaginary/tdouble);
}
TComplex TComplex::operator/(const int tint) const{
    return TComplex(real/tint, imaginary/tint);
}
TComplex TComplex::operator/(const TComplex& tcomplex) const{
    return TComplex(

        (this->real*tcomplex.real+this->imaginary*tcomplex.imaginary)
                                    /                                // real part
        (pow(tcomplex.real,2)+pow(tcomplex.imaginary,2))

        ,

        (this->imaginary*tcomplex.real-this->real*tcomplex.imaginary)
                                    /                                // imaginary part
        (pow(tcomplex.real,2)+pow(tcomplex.imaginary,2))

        );
}
double TComplex::get_real() const {
    return real;
}
double TComplex::get_image() const{
    return imaginary;
}
double TComplex::magnitude() const{
    return ((this->real*this->real)+(this->imaginary*this->imaginary));
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
}
//////////////////////////////////Outside of class functions///////////////////////////////////
TComplex sqrt(const TComplex& tcomplex){
    return tcomplex.sqrt_t(); // We need this goofy ahh method to override sqrt from <math.h>
}
TComplex pow(const TComplex& tcomplex, int y){
    return tcomplex.pow_t(y); // Read 145:31
}
bool is_complex_from_string(const std::string &tstring){
    std::regex complexRegex(R"((-?\d+(\.\d+)?)([+-]\d+(\.\d+)?)i)");
    std::smatch match;
    if (std::regex_match(tstring, match, complexRegex)) return true;
    else return false;
}
