#include "sine.h"
template <typename T>
Sine<T>::~Sine() {}
template<typename T>
Array<T> Sine<T>::differentiate(unsigned int accuracy)
{
    Array<T> result(accuracy);
    for (unsigned i = 0; i < accuracy; i++){
        switch(i%4){
        case 0:
            result.push_back(0);
            break;
        case 1:
            result.push_back(1);
            break;
        case 2:
            result.push_back(0);
            break;
        case 3:
            result.push_back(-1);
            break;
        }
    }
    return result;
}
template class Sine<double>;
template class Sine<TComplex>;
