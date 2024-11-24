#include "array.h"
#include <cmath>
template <typename number>
Array<number>::Array() {
    size = 0;
    numbers = nullptr;
    sentinel = nullptr;
}
template <typename number>
Array<number>::Array(int n): Array() {
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
template <typename number>
Array<number>::~Array(){
    delete[] numbers;
    delete[] sentinel;
}
template <typename number>
std::istream& operator>>(std::istream& stream, Array<number>& array){
    for(size_t i = 0; i < array.size; i++)
    {
        stream>>array.numbers[i];
        array.sentinel[i] = 1;
    }
    fflush(stdin);
    return stream;
}
template <typename number>
std::ostream& operator<<(std::ostream& stream, const Array<number>& array){
    if (array.size == 0) return stream<<"[]";
    stream<<"[";
    for(size_t i = 0; i < array.size-1; i++)
    {
        stream<<array.numbers[i]<<", ";
    }
    if (array.size > 0) {
        stream<<array.numbers[array.size-1]<<"]"<<std::endl;
    }
    return stream;
}
template <typename number>
size_t Array<number>::get_size() {
    return size;
}
template <typename number>
number Array<number>::arithmetic_mean(){
    int count = 0;
    number values = 0;
    for(size_t i = 0; i < size; i++) {
        values = values + numbers[i];
        count++;
    }
    return values/count;
}
template <typename number>
number Array<number>::root_mean_square_deviation() {
        double count = 0;
        number sum = 0;
        for(size_t i = 0; i < size; i++) {
            sum = sum + (number) ((numbers[i]-arithmetic_mean()) * ((numbers[i]-arithmetic_mean())));
            count++;
        }
        if ((int)count==1) return 0;
        return sqrt(sum*(1/(count-1)));
}
template <typename number>
number* Array<number>::get_numbers() const{
    return this->numbers;
}
template <typename number>
bool *Array<number>::get_sentinel() const
{
    return this->sentinel;
}
template <typename number>
void Array<number>::resize(int n) {
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
template <typename number>
void Array<number>::sort(bool ascending){
    size_t length = size;
    while (length--){
        bool swapped = false;
        if (ascending){
            for (size_t i = 0; i < length; i++){
                if (numbers[i] > numbers[i+1]){
                    std::swap(numbers[i], numbers[i+1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        else{
            for (size_t i = 0; i < length; i++){
                if (numbers[i] < numbers[i+1]){
                    std::swap(numbers[i], numbers[i+1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }
}
template <typename number>
void Array<number>::set_numbers(int n,number j){
    numbers[n]=j;
    sentinel[n]=1;
}
template <typename number>
void Array<number>::push_back(number j) {
    for (size_t i = 0; i < size; i++) {
        if (sentinel[i]==0) {
            numbers[i]=j;
            sentinel[i]=1;
            return;
        }
    }
}
template class Array<TComplex>;
template class Array<double>;
template std::istream& operator>>(std::istream& stream, Array<TComplex>& array);
template std::istream& operator>>(std::istream& stream, Array<double>& array);
template std::ostream& operator<<(std::ostream& stream, const Array<TComplex>& array);
template std::ostream& operator<<(std::ostream& stream, const Array<double>& array);


