#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPainter>
#include "sine.h"
#include "sineintegral.h"
#include "sstream"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class DrawingWindow : public QWidget {
public:
    DrawingWindow(int deg_, bool s_ , int from, int before, QWidget *parent = nullptr) : QWidget(parent) {
        deg = deg_;
        s = s_;
        b=before;
        f=from;
        setFixedSize(800,800);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        Function<TComplex>* object = nullptr;
        if (s==0) object = new Sine<TComplex>(deg*2);
        else object = new SineIntegral<TComplex>(deg*2);
        TComplex ar;
        painter.setPen(Qt::blue);
        double x1=f, y1, x2=f, y2;
        std::stringstream ss_;
        ar = TComplex(0);
        y1 = (object->solve_for_x(ar)).get_real();
        double scale = 800 / (b - f);
        while(x1<b) {
            x2+=0.1;
            ar = TComplex(x2);
            y2 = (object->solve_for_x(ar)).get_real();
            painter.drawPoint(((x1-f)*scale),(y1*scale+400));
            x1=x2;
            y1=y2;
        }
        delete object;
    }

private:
    int deg;
    bool s;
    int f, b;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void showDrawingWindow(int, bool, int, int);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
