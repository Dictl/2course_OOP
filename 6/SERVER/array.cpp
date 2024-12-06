#include "array.h"
#include <cmath>
template <typename N>
Array<N>::Array() {
    size = 0;
    numbers = nullptr;
    sentinel = nullptr;
}
template <typename N>
Array<N>::Array(int n): Array() {
    if (n<=0) {
        return;
    }
    size = n;
    numbers = new N[size]();
    sentinel = new bool[size]();
    for (size_t i = 0; i < size; i++) {
        sentinel[i]=0;
    }
}
template <typename N>
Array<N>::~Array(){
    delete[] numbers;
    delete[] sentinel;
}
template <typename N>
std::istream& operator>>(std::istream& stream, Array<N>& array){
    for(size_t i = 0; i < array.size; i++)
    {
        stream>>array.numbers[i];
        array.sentinel[i] = 1;
    }
    fflush(stdin);
    return stream;
}
template <typename N>
std::ostream& operator<<(std::ostream& stream, const Array<N>& array){
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
template <typename N>
size_t Array<N>::get_size() {
    return size;
}
template <typename N>
N Array<N>::arithmetic_mean(){
    int count = 0;
    N values = 0;
    for(size_t i = 0; i < size; i++) {
        values = values + numbers[i];
        count++;
    }
    return values/count;
}
template <typename N>
N Array<N>::root_mean_square_deviation() {
        double count = 0;
        N sum = 0;
        for(size_t i = 0; i < size; i++) {
            sum = sum + (N) ((numbers[i]-arithmetic_mean()) * ((numbers[i]-arithmetic_mean())));
            count++;
        }
        if ((int)count==1) return 0;
        return sqrt(sum*(1/(count-1)));
}
template <typename N>
N* Array<N>::get_numbers() const{
    return this->numbers;
}
template <typename N>
bool *Array<N>::get_sentinel() const
{
    return this->sentinel;
}
template <typename N>
void Array<N>::resize(int n) {
    if (size == 0 && n <= 0) {
        return;
    }
    if (size == 0) {
        numbers = new N[n]();
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
    N* new_numbers = new N[n]();
    for (size_t i = 0; i < max_size; i++) {
        new_numbers[i]=numbers[i];
    }
    delete[] numbers;
    delete[] sentinel;
    sentinel = new_sentinel;
    numbers = new_numbers;
    size = n;
}
template <typename N>
void Array<N>::sort(bool ascending){
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
template <typename N>
void Array<N>::set_numbers(int n,N j){
    numbers[n]=j;
    sentinel[n]=1;
}
template <typename N>
void Array<N>::push_back(N j) {
    for (size_t i = 0; i < size; i++) {
        if (sentinel[i]==0) {
            numbers[i]=j;
            sentinel[i]=1;
            return;
        }
    }
}
template class Array<number>;
template class Array<double>;
template std::istream& operator>>(std::istream& stream, Array<TComplex>& array);
template std::istream& operator>>(std::istream& stream, Array<double>& array);
template std::ostream& operator<<(std::ostream& stream, const Array<TComplex>& array);
template std::ostream& operator<<(std::ostream& stream, const Array<double>& array);


