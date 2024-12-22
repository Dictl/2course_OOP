#ifndef SINEINTEGRAL_H
#define SINEINTEGRAL_H
#include "function.h"

template <typename T>
class SineIntegral : public Function<T>
{
public:
    SineIntegral(unsigned accuracy) : Function<T>(accuracy, differentiate(accuracy)) {}
    ~SineIntegral();
private:
    Array<T> differentiate(unsigned accuracy);
};
#endif // SINEINTEGRAL_H
