/*#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}*/
#include <iostream>
#include "polynom.h"
#include "application.cpp"
using namespace std;

int main()
{
    setlocale(LC_ALL,"Russian");
    size_t size;
    cout << "Enter polynom size:";
    cin >> size;
    Polynom* poly = new Polynom(size);
    cout << "Enter An, and then polynom's roots:";
    cin >>* poly;
    poly->set_display_format(1);
    cout <<* poly;
    cout << "Enter new size:";
    cin >> size;
    poly->resize(size);
    cout <<* poly;
    return EXIT_SUCCESS;
}
