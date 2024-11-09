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
    friend istream& operator>>(istream& stream, Array& array); //перегруз ввода-вывода
    friend ostream& operator<<(ostream& stream, const Array& array);
    void resize(int n);
    void sort(bool ascending);
    number arithmetic_mean(); //Среднее алгебраическое
    number root_mean_square_deviation(); //Среднеквадратичное отклонение
    size_t getSize();
    void setNumbers(int n,number j);

private:
    size_t size; //size_t - обозванный *unsinged* long long int для размеров массивов etc
    number* numbers;
};

#endif // ARRAY_H
