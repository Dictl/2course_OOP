
#include "server.h"
#include "interface.h"
#include <QApplication>
#include <sstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(argc, argv,nullptr);
    w.show();
    return a.exec();

    /*std::stringstream a;
    a << "5 1 65533 based holy IT WORKS??!!! GYATT";
    std::string str;
    a >> str;
    a >> str;
    a.clear();
    str = a.str();
    std::regex regex_pattern(R"((?:\d+\s+){3})");
    std::string result = std::regex_replace(str, regex_pattern, "$1");
    std::cout<< result;*/
}
