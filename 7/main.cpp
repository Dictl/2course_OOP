#include <iostream>
#include "sine.h"
#include "sineintegral.h"

int main(int argc, char *argv[])
{
    SineIntegral<TComplex> sine(7);
    std::cout << sine.solve_for_x(1);
    exit(0);
}
