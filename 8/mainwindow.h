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
    DrawingWindow(int deg_, bool s_ , QWidget *parent = nullptr) : QWidget(parent) {
        deg = deg_;
        s = s_;
        setFixedSize(800,800);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        std::stringstream iss;
        std::stringstream ss;
        if(s==0){
        QPainter painter(this);
        Sine<TComplex> sine_object(deg);
        TComplex ar;
        ss>>ar;
        std::string t;
        iss>>t;
        painter.setPen(Qt::blue);
        double x1=0, y1, x2, y2;
        std::stringstream ss_;
        ar = double(0);
        ss_<<sine_object.solve_for_x(ar);
        ss_>>t;
        y1=std::stoi(t);

          for(double i=0.001; i<400; i+=0.001){
            //if(y1>400){break;}
            std::stringstream ss_;
            ar = double(i);
            ss_<<sine_object.solve_for_x(ar);
            std::string t;
            ss_>>t;
            y2=std::stoi(t);
           painter.drawLine(x1+200,-y1+350,i+200,-y2+350);
            x1=i;
            y1=y2;
           }

        }
        else{
            QPainter painter(this);
            SineIntegral<TComplex> sineIntegral_object(deg);
            TComplex ar;
            ss>>ar;
            std::string t;
            iss>>t;
            painter.setPen(Qt::blue);
            double x1=0, y1, x2, y2;
            std::stringstream ss_;
            ar = double(0);
            ss_<<sineIntegral_object.solve_for_x(ar);
            ss_>>t;
            y1=std::stoi(t);


            for(double i=0.001; i<400; i+=0.001){

                std::stringstream ss_;
                ar = double(i);
                ss_<<sineIntegral_object.solve_for_x(ar);
                std::string t;
                ss_>>t;
                y2=std::stoi(t);
                painter.drawLine(x1+200,-y1+350,i+200,-y2+350);
                x1=i;
                y1=y2;
            }

        }

    }

private:
    int deg;
    bool s;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void showDrawingWindow(int, bool);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
