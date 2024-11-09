/*#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}*/
#include <iostream>
#include "array.h"
#include "application.cpp"
using namespace std;

int main()
{
    setlocale(LC_ALL,"Russian");
<<<<<<< Updated upstream
    size_t size;
    cout << "Enter array size:";
    cin >> size;
    Array* array = new Array(size);
    cout << "Array's elements:";
    cin >> *array;
    cout << "Enter new array size:";
    cin >> size;
    cout << *array << endl << array->arithmetic_mean() << endl << array->root_mean_square_deviation();
    delete array;




    return EXIT_SUCCESS;

=======
    basis object;
    object.menu();
>>>>>>> Stashed changes
}
