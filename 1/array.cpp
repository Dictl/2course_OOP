#include "array.h"
#include <math.h>
Array::Array() {
    size = 0;
    numbers = nullptr;
}
Array::Array(int n): Array() {
    if (n<=0)
    {
        return;
    }
    size = n;
    numbers = new number[size]();
}
void Array::resize(int n) {
    if (size == 0 && n <= 0) {
        return;
    }
    if (size == 0) {
        numbers = new number[n]();
        size = (size_t) n;
        return;
    }
    if (n<=0) {
        delete[] numbers;
        numbers = nullptr;
        size = 0;
        return;
    }
    number* new_numbers = new number[n]();
    size_t max_size = size >= (size_t) n ? (size_t) n : size;
    for (size_t i = 0; i < max_size; i++) {
        new_numbers[i]=numbers[i];
    }
    delete[] numbers;
    numbers = new_numbers;
    size = n;
}
void Array::sort(bool ascending){
    size_t length = size;
    while (length--){
        bool swapped = false;
        if (ascending){
            for (size_t i = 0; i < length; i++){
                if (numbers[i] > numbers[i+1]){
                    swap(numbers[i], numbers[i+1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        else{
            for (size_t i = 0; i < length; i++){
                if (numbers[i] < numbers[i+1]){
                    swap(numbers[i], numbers[i+1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }
}
Array::~Array(){
    delete[] numbers;
}
istream& operator>>(istream& stream, Array& array){
    for(size_t i = 0; i < array.size; i++)
    {
        stream>>array.numbers[i];
    }
    fflush(stdin);
    return stream;
}
ostream& operator<<(ostream& stream, const Array& array){
    if (array.size == 0) return stream<<"[]";
    stream<<"[";
    for(size_t i = 0; i < array.size-1; i++)
    {
        stream<<array.numbers[i]<<", ";
    }
    if (array.size > 0) {
        stream<<array.numbers[array.size-1]<<"]"<<endl;
    }
    return stream;
}
number Array::arithmetic_mean(){
    int count = 0;
    number values = 0;
    for(size_t i = 0; i < size; i++)
    {
        values += numbers[i];
        count++;
    }
    return values/(number)count;
}
number Array::root_mean_square_deviation()
{
    int count = 0;
    number sum = 0;
    for(size_t i = 0; i < size; i++)
    {
        sum += (number) (pow(numbers[i]-arithmetic_mean(), 2));
        count++;
    }
    if (count==1) return 0;
    return sqrt((1/ (number) (count-1)) * sum);
}
