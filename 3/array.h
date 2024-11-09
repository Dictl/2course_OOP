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
    void resize(int n);
    void sort(bool ascending);
    number arithmetic_mean();
    number root_mean_square_deviation();
    size_t get_size();
    void set_numbers(int n,number j);
    number* get_numbers() const;
    void push_back(number j);

private:
    bool* sentinel;
    size_t size;
    number* numbers;
};

#endif // ARRAY_H
