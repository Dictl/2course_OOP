#include "array.h"
#include <cmath>
Array::Array() {
    size = 0;
    numbers = nullptr;
    sentinel = nullptr;
}
Array::Array(int n): Array() {
    if (n<=0) {
        return;
    }
    size = n;
    numbers = new number[size]();
    sentinel = new bool[size]();
    for (size_t i = 0; i < size; i++) {
        sentinel[i]=0;
    }
}
Array::~Array(){
    delete[] numbers;
    delete[] sentinel;
}
istream& operator>>(istream& stream, Array& array){
    for(size_t i = 0; i < array.size; i++)
    {
        stream>>array.numbers[i];
        array.sentinel[i] = 1;
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
size_t Array::get_size() {
    return size;
}
number Array::arithmetic_mean(){
    int count = 0;
    number values = 0;
    for(size_t i = 0; i < size; i++) {
        values = values + numbers[i];
        count++;
    }
    return values/count;
}
number Array::root_mean_square_deviation()
    {
        double count = 0;
        number sum = 0;
        for(size_t i = 0; i < size; i++) {
            sum = sum + (number) ((numbers[i]-arithmetic_mean()) * ((numbers[i]-arithmetic_mean())));
            count++;
        }
        if ((int)count==1) return 0;
        return sqrt(sum*(1/(count-1)));
}
number* Array::get_numbers() const{
    return this->numbers;
}

bool *Array::get_sentinel() const
{
    return this->sentinel;
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
    size_t max_size = size >= (size_t) n ? (size_t) n : size;
    bool* new_sentinel = new bool[n]();
    if (max_size > size){
        for (size_t i = 0; i < size-1; i++) {
            new_sentinel[i]=1;
        }
    }
    else {
        for (size_t i = 0; i < max_size; i++) {
            new_sentinel[i]=1;
        }
    }
    number* new_numbers = new number[n]();
    for (size_t i = 0; i < max_size; i++) {
        new_numbers[i]=numbers[i];
    }
    delete[] numbers;
    delete[] sentinel;
    sentinel = new_sentinel;
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
void Array::set_numbers(int n,number j){
    numbers[n]=j;
    sentinel[n]=1;
}
void Array::push_back(number j) {
    for (size_t i = 0; i < size; i++) {
        if (sentinel[i]==0) {
            numbers[i]=j;
            sentinel[i]=1;
            return;
        }
    }
}
