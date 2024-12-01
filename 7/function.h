#ifndef FUNCTION_H
#define FUNCTION_H
#include "polynom.h"

template <typename T>
class Function : public Polynom<T>
{
public:
    Function();
    Function(int accuracy, Array<T> derivatives);
    ~Function();
};

#endif // FUNCTION_H

int factorial(int i);