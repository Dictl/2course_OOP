#include "function.h"

template <typename T>
Function<T>::Function() {
    this->coefficients = new Array<T>;
    this->a_n = 1;
}
template<typename T>
Function<T>::Function(int accuracy, Array<T> derivatives) : Function() {
    if (accuracy < 0) return;
    else this->size = accuracy-1;
    Array<T> derivatives_2 (derivatives.get_size());
    for (size_t i = 0; i < derivatives.get_size(); i++){
        derivatives_2.get_numbers()[i]=derivatives.get_numbers()[derivatives.get_size()-i-1];
    } // I HAVE TO REVERSE IT PLEASE SEND HELP T_T

    int j;
    if (derivatives_2.get_numbers()[0] == 0 || accuracy % 2 == 1) {
        j = accuracy;
    }  // depending on accuracy first coefficient might or might not be a zero.
    else{
        j = accuracy-1;
    }


    this->coefficients = new Array<T>(derivatives.get_size());
    for (int i = 0; i < accuracy; i++) {
        this->coefficients->get_numbers()[i] = (derivatives_2.get_numbers()[i] / factorial(j));
        j--;
    }
}
template<typename T>
Function<T>::~Function(){}
template class Function<double>;
template class Function<TComplex>;
int factorial(int i) {
    if (i==0) return 1;
    else return i*factorial(i-1);
}
