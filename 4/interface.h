#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>

#include "array.h"
#include "polynom.h"
#include <sstream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_polynom_n_clicked();

    void on_resize_cof_clicked();

    void on_polynom_x_clicked();

    void on_change_cof_a_clicked();

    void on_change_roots_clicked();

    void on_polynom_1_clicked();

    void on_polynom_2_clicked();

    void on_pushButton_clicked();

private:

    Ui::MainWindow *ui;

};
#endif // INTERFACE_H
