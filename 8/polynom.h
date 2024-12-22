#ifndef POLYNOM_H
#define POLYNOM_H
#include "array.h"

template <typename number>
class Polynom
{

public:
    Polynom();
    Polynom(Array<number> &_array);
    Polynom(size_t size);
    ~Polynom();
    template <typename T>
    friend std::istream& operator>>(std::istream& stream, Polynom<T>& polynom);
    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const Polynom<T>& polynom);
    Array<number> get_roots();
    Array<number>* get_coefficients() const; // access to coefficients (read-only)
    number solve_for_x(number x);
    void set_display_format(bool _expanded); // whether to expand brackets or not
    void set_a_n(number _a_n);
    void resize(int n);
    void change_root(int index, number j);
    void count_coefficients();
    int are_roots_full(); /*brand new method to prevent from buggy display when not all
                             roots are defined*/
protected:
    Array<number>* roots;
    Array<number>* coefficients;
    number a_n;
    size_t size;
private:
    bool expanded = false;

};

#endif // POLYNOM_H
