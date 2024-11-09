#pragma once
#ifndef ARRAY_H
#define ARRAY_H
#include "number.h"
#include <iostream>
using namespace std;


class Array
{
public:
    Array();
    Array(int n);
    ~Array();
    friend istream& operator>>(istream& stream, Array& array);
    friend ostream& operator<<(ostream& stream, const Array& array);
    size_t get_size();
    number arithmetic_mean();
    number root_mean_square_deviation();
    number* get_numbers() const;
    void resize(int n);
    void sort(bool ascending);
    void set_numbers(int n,number j);
    void push_back(number j);

private:
    bool* sentinel; // 1 if this index was defined, 0 if it's garbage
    size_t size;
    number* numbers;
};

#endif // ARRAY_H
