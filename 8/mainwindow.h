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
        std::stringstream iss;
        std::stringstream ss;
        if(s==0){
            QPainter painter(this);
            Sine<TComplex> sine_object(deg*2);
            TComplex ar;
        ss>>ar;
        std::string t;
        iss>>t;
        painter.setPen(Qt::blue);
        double x1=f, y1, x2=f, y2;
        std::stringstream ss_;
        ar = double(x1);
        ss_<<sine_object.solve_for_x(ar);
        ss_>>t;
        y1=std::stoi(t);
        double scale = 800 / (b - f);
        while(x1<b){
            x2+=0.1;
            std::stringstream ss_;
            ar = double(x2);
            ss_<<sine_object.solve_for_x(ar);
            std::string t;
            ss_>>t;
            y2=std::stoi(t);
            painter.drawPoint(((x1-f)*scale),(y1*scale+400));
            //painter.drawLine(((x1-f)*scale),(y1*scale+400),((x2-f)*scale),(y2*scale+400));
            x1=x2;
            y1=y2;
        }

        }else{
            QPainter painter(this);
            SineIntegral<TComplex> sineIntegral_object(deg*2);
            TComplex ar;
            ss>>ar;
            std::string t;
            iss>>t;
            painter.setPen(Qt::blue);
            double x1=f, y1, x2=f, y2;
            std::stringstream ss_;
            ar = double(0);
            ss_<<sineIntegral_object.solve_for_x(ar);
            ss_>>t;
            y1=std::stoi(t);

            while(x1<b){
                x2+=0.001;
                std::stringstream ss_;
                ar = double(x2);
                ss_<<sineIntegral_object.solve_for_x(ar);
                std::string t;
                ss_>>t;
                y2=std::stoi(t);
                painter.drawLine(x1-f,-y1+350,x2-f,-y2+350);
                x1=x2;
                y1=y2;
            }

        }

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
