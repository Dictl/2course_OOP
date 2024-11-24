#include <QCoreApplication>
#include "server.h"
#include <sstream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server(argc, argv);
    return a.exec();


}
