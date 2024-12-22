#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //DrawingWindow *drawingWindow = new DrawingWindow(3, 0);
    //drawingWindow->show();
    MainWindow w;
    w.show();
    return a.exec();
}
