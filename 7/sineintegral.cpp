#include "sineintegral.h"

template <typename T>
SineIntegral<T>::~SineIntegral() {}
template<typename T>
Array<T> SineIntegral<T>::differentiate(unsigned int accuracy)
{
    Array<T> result(accuracy);
    for (unsigned i = 0; i < accuracy; i++){
        switch(i%4){
        case 0:
            result.push_back(1);
            break;
        case 1:
            result.push_back(0);
            break;
        case 2:
            result.push_back(-1);
            break;
        case 3:
            result.push_back(0);
            break;

        }
    }
    return result;
}
template class SineIntegral<double>;
template class SineIntegral<TComplex>;
