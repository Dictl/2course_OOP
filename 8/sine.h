#ifndef SINE_H
#define SINE_H
#include "function.h"

template <typename T>
class Sine : public Function<T>
{
public:
    Sine(unsigned accuracy) : Function<T>(accuracy, differentiate(accuracy)) {}
    ~Sine();
private:
    Array<T> differentiate(unsigned accuracy);
};

#endif // SINE_H
