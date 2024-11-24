#include "polynom.h"
template <typename number>
Polynom<number>::Polynom() {
    Array<number> roots = {0};
    size = 0;
}
template <typename number>
Polynom<number>::Polynom(size_t _size) : Polynom() {
    Array<number>* for_roots = new Array<number>(_size);
    roots = for_roots;
    size = _size;
}
template <typename number>
Polynom<number>::~Polynom() {
    delete[] coefficients;
};
template <typename number>
std::istream& operator>>(std::istream& stream, Polynom<number>& polynom) {
    number root;
    stream >> polynom.a_n;
    if (polynom.size==0){
        return stream;
    }
    for(size_t i = 0; i < polynom.size; i++)
    {
        stream >> root;
        polynom.roots->push_back(root);
    }
    polynom.count_coefficients();
    return stream;
}
template <typename number>
std::ostream& operator<<(std::ostream& stream, const Polynom<number>& polynom) {
    char op_brace;
    char en_brace;
    if (polynom.size == 0)
    {
        stream << polynom.a_n;
        return stream;
    }
    if (!polynom.expanded){
        polynom.a_n == 0 ? stream << "\0" : stream << "(";
        stream<<polynom.a_n;
        polynom.a_n == 0 ? stream << "\0" : stream << ")";
        stream<<"(";

        for(size_t i = 0; i < polynom.size; i++)
        {
            if (polynom.roots->get_numbers()[i]<0) stream<<"(x" << "+" << polynom.roots->get_numbers()[i]*-1 << ")";
            else stream<<"(x" << "-" << polynom.roots->get_numbers()[i] << ")";
        }
        stream << ")";
    }
    else {
        for (size_t i = 0; i<polynom.size; i++){
            if(polynom.coefficients->get_numbers()[i] == 0)
            {
                continue;
            }
            if ((polynom.coefficients->get_numbers()[i]*polynom.a_n) == 0){
                op_brace = '\0';
                en_brace = '\0';
            }
            else
            {
                op_brace = '(';
                en_brace = ')';
            }
            if (polynom.size-i!=1 && (polynom.a_n*polynom.coefficients->get_numbers()[i] != 1)){
                if ((polynom.a_n*polynom.coefficients->get_numbers()[i]) < 0){
                    stream << "-" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i]*-1 << en_brace << "x^" << (int) polynom.size-i;
                }
                else{
                    if (i==0){
                        stream << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i] << en_brace << "x^" << (int) polynom.size-i;
                    }
                    else stream << "+" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i] << en_brace << "x^" << (int) polynom.size-i;
                }
            }
            else if (polynom.a_n*polynom.coefficients->get_numbers()[i] == 1 && polynom.size-i!=1) {
                if ((polynom.a_n*polynom.coefficients->get_numbers()[i]) < 0){
                    stream << "-" << "x^" << (int) polynom.size-i;
                }
                else {
                    if (i==0){
                        stream << "x^" << (int) polynom.size-i;
                    }
                    else stream << "+" << "x^" << (int) polynom.size-i;
                }
            }
            else if (polynom.a_n*polynom.coefficients->get_numbers()[i] != 1) {
                if ((polynom.a_n*polynom.coefficients->get_numbers()[i]) < 0){
                    stream << "-" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i]*-1 << en_brace << "x";
                }
                else{
                    if (i == 0){
                        stream << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i] << en_brace << "x";
                    }
                    else stream << "+" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i] << en_brace << "x";
                }
            }
            else {
                if ((polynom.a_n*polynom.coefficients->get_numbers()[i]) < 0){
                    stream << "-" << "x";
                }
                else stream << "+" << "x";
            }
        }
        if ((polynom.coefficients->get_numbers()[polynom.size]*polynom.a_n) == 0){
            op_brace = '\0';
            en_brace = '\0';
        }
        else
        {
            op_brace = '(';
            en_brace = ')';
        }
        if ((polynom.a_n*polynom.coefficients->get_numbers()[polynom.size]) < 0){
            stream << "-" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[polynom.size]*-1<<en_brace<<std::endl;
        }
        else{
            stream << "+" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[polynom.size]<<en_brace<<std::endl;
        }
    }
    return stream;
}
template<> // we specialize TComplex because every other type should work just fine
std::ostream& operator<<(std::ostream& stream, const Polynom<TComplex>& polynom) {
    char op_brace;
    char en_brace;
    bool braces;
    if (polynom.size == 0)
    {
        stream << polynom.a_n;
        return stream;
    }
    if (!polynom.expanded){
        polynom.a_n.get_image() == ( double )0 ? stream << "\0" : stream << "(";
        stream<<polynom.a_n;
        polynom.a_n.get_image() == ( double )0 ? stream << "\0" : stream << ")";
        stream<<"(";

        for(size_t i = 0; i < polynom.size; i++)
        {
            polynom.roots->get_numbers()[i].get_image() == 0 ? braces = 0 : braces = 1;

            if (braces){
                if (polynom.roots->get_numbers()[i].get_real()<0) stream<<"(x" << "+(" << polynom.roots->get_numbers()[i]*-1<<"))";
                else stream<<"(x"<< "-(" << polynom.roots->get_numbers()[i]<<"))";
            }
            else{
                if (polynom.roots->get_numbers()[i].get_real()<0) stream<<"(x" << "+" << polynom.roots->get_numbers()[i]*-1 << ")";
                else stream<<"(x" << "-" << polynom.roots->get_numbers()[i] << ")";
            }
        }
        stream << ")";
    }
    else {

        for (size_t i = 0; i<polynom.size; i++){
            if(polynom.coefficients->get_numbers()[i].get_real() == 0 && polynom.coefficients->get_numbers()[i].get_image() == 0)
            {
                continue;
            }
            if ((polynom.coefficients->get_numbers()[i]*polynom.a_n).get_image() == 0){
                op_brace = '\0';
                en_brace = '\0';
            }
            else
            {
                op_brace = '(';
                en_brace = ')';
            }
            if (polynom.size-i!=1 && (polynom.a_n*polynom.coefficients->get_numbers()[i] != TComplex(1))){
                if ((polynom.a_n*polynom.coefficients->get_numbers()[i]).get_real()< 0){
                    stream << "-" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i]*-1 << en_brace << "x^" << (int) polynom.size-i;
                }
                else{
                    if (i==0){
                        stream << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i] << en_brace << "x^" << (int) polynom.size-i;
                    }
                    else stream << "+" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i] << en_brace << "x^" << (int) polynom.size-i;
                }
            }
            else if (polynom.a_n*polynom.coefficients->get_numbers()[i] == TComplex(1) && polynom.size-i!=1) {
                if ((polynom.a_n*polynom.coefficients->get_numbers()[i]).get_real()<0){
                    stream << "-" << "x^" << (int) polynom.size-i;
                }
                else {
                    if (i==0){
                        stream << "x^" << (int) polynom.size-i;
                    }
                    else stream << "+" << "x^" << (int) polynom.size-i;
                }
            }
            else if (polynom.a_n*polynom.coefficients->get_numbers()[i] != TComplex(1)) {
                if ((polynom.a_n*polynom.coefficients->get_numbers()[i]).get_real()<0){
                    stream << "-" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i]*-1 << en_brace << "x";
                }
                else{
                    if (i == 0){
                        stream << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i] << en_brace << "x";
                    }
                    else stream << "+" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[i] << en_brace << "x";
                }
            }
            else {
                if ((polynom.a_n*polynom.coefficients->get_numbers()[i]).get_real() <0){
                    stream << "-" << "x";
                }
                else stream << "+" << "x";
            }
        }
        if ((polynom.coefficients->get_numbers()[polynom.size]*polynom.a_n).get_image() == 0){
            op_brace = '\0';
            en_brace = '\0';
        }
        else
        {
            op_brace = '(';
            en_brace = ')';
        }
        if ((polynom.a_n*polynom.coefficients->get_numbers()[polynom.size]).get_real() < 0){
            stream << "-" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[polynom.size]*-1<<en_brace<<std::endl;
        }
        else{
            stream << "+" << op_brace << polynom.a_n*polynom.coefficients->get_numbers()[polynom.size]<<en_brace<<std::endl;
        }
    }
    return stream;
}
template <typename number>
Array<number> Polynom<number>::get_roots(){
    return *roots;
}
template <typename number>
Array<number>* Polynom<number>::get_coefficients() const{
    return this->coefficients;
}
template <typename number>
number Polynom<number>::solve_for_x(number x){
    number result = 0;
    for (size_t i = 0; i < size+1; i++){
        if (size-i > 0) result = result + a_n * pow( x ,size-i) * ( coefficients->get_numbers()[i] );
        else result = result + a_n * (coefficients->get_numbers()[i]);

    }
    return result;
}
template <typename number>
void Polynom<number>::set_display_format(bool _expanded){
    expanded = _expanded;
    return;
}
template <typename number>
void Polynom<number>::set_a_n(number _a_n){
    a_n = _a_n;
    return;
}
template <typename number>
void Polynom<number>::resize(int n){
    if (size == 0 && n <= 0) {
            return;
    }
    if (n<=0) {
        delete coefficients;
        this->roots->resize(n);
        size = 0;
        return;
    }
    this->roots->resize(n);
    delete coefficients;
    Array<number>* _coefficients = new Array<number>(n+1);
    coefficients = _coefficients;
    size = n;
    this->count_coefficients();
}
template <typename number>
void Polynom<number>::change_root(int index, number j) {
    this->roots->set_numbers(index,j);
    this->count_coefficients();

}
template <typename number>
void Polynom<number>::count_coefficients(){
    bool multiplied;
    bool moved_on = false;
    this->coefficients = new Array<number>(this->size+1); // an array representation of the coefficients
    this->coefficients->set_numbers(this->size, this->roots->get_numbers()[0]*-1); // the root (5+0i for example)
    this->coefficients->set_numbers(this->size-1, 1); // the 'x' part, the complete brace: (x-(5+0i))
    for (size_t i = 1; i < this->size; i++){ // for every root except the first one
        multiplied = false; // we need to multiply 1 time per root, and then *only* sum up
        moved_on = false; // if we moved onto the next position because the current coefficient was zero
        for (size_t j = 0; j < this->size; j++){
            if (this->coefficients->get_numbers()[j] == 0 && !moved_on){
                continue; // gonna find the parts of the polynom that exist and then expand the brackets
            }
            if (j > 0 && (this->coefficients->get_numbers()[j-1] == 0 && !moved_on)) this->coefficients->set_numbers(j-1, 1);
            // multiplying an x by an x results in an x^2 and so on

            if (!multiplied) {
                this->coefficients->set_numbers(j,this->coefficients->get_numbers()[j] * (this->roots->get_numbers()[i] * -1));
                multiplied = true; // multiplying by the root and then just summing up
            }

            if (this->coefficients->get_numbers()[j+1] == 0){
                moved_on = true; //if coefficient zeroed somehow after the expansion we don't wanna overwrite 0 with 1
                continue;
            }
            if (j+1 < this->size+1){
                this->coefficients->set_numbers(j,this->coefficients->get_numbers()[j] + this->coefficients->get_numbers()[j+1]); //muptiplying a number by an x may be iterpreted just as making it a coefficient of the next degree
                this->coefficients->set_numbers(j+1,(this->roots->get_numbers()[i]*-1) * this->coefficients->get_numbers()[j+1]); //mupltiplying the last part of the bracket
                if (this->coefficients->get_numbers()[j] == 0) moved_on = true; // we don't need to mark the zeroed bit of the polynomial as 1, so trigger moved_on
            } // and so every bracket will continously muptiply by an x and every root except the first
        }
    }
}
template <typename number>
int Polynom<number>::are_roots_full()
{
    for (size_t i = 0; i < roots->get_size(); i++){
        if(roots->get_sentinel()[i] == 0)
        {
            return i;
        }
    }
    return -1;
}
template class Polynom<TComplex>;
template class Polynom<double>;
template std::istream& operator>>(std::istream& stream, Polynom<TComplex>& polynom);
template std::istream& operator>>(std::istream& stream, Polynom<double>& polynom);
template std::ostream& operator<<(std::ostream& stream, const Polynom<double>& polynom);


