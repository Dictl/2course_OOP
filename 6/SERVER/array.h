#pragma once
#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include "number.h"

template <typename N>
class Array
{
public:
    Array();
    Array(int n);
    ~Array();
    template <typename T>
    friend std::istream& operator>>(std::istream& stream, Array<T>& array);
    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const Array<T>& array);
    size_t get_size();
    N arithmetic_mean();
    N root_mean_square_deviation();
    N* get_numbers() const;
    bool* get_sentinel() const;
    void resize(int n);
    void sort(bool ascending);
    void set_numbers(int n,N j);
    void push_back(N j);

private:
    bool* sentinel; // 1 if this index was defined, 0 if it's garbage
    size_t size;
    N* numbers;
};

#endif // ARRAY_H
