#ifndef POLYNOM_H
#define POLYNOM_H
#include "array.h"

class Polynom
{

public:
    Polynom();
    Polynom(Array &_array);
    Polynom(size_t size);
    ~Polynom();
    friend istream& operator>>(istream& stream, Polynom& polynom);
    friend ostream& operator<<(ostream& stream, const Polynom& polynom);
    Array get_roots();
    Array* get_coefficients() const; // access to coefficients (read-only)
    number solve_for_x(number x);
    void set_display_format(bool _expanded); // whether to expand brackets or not
    void set_a_n(number _a_n);
    void resize(int n);
    void change_root(int index, number j);
    void count_coefficients();
private:
    bool expanded = false;
    Array* coefficients;
    Array* roots;
    size_t size;
    number a_n;
};

#endif // POLYNOM_H
