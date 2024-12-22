#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "function.h"
#include "array.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QIntValidator>

QString degree, point;

Array<TComplex> arr_object;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QIntValidator *les = new QIntValidator(0,100000,0);
    ui->degree_->setValidator(les);
    ui->sin_->setChecked(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    std::stringstream iss;
    std::stringstream ss;
    if(ui->sin_->isChecked()){
        degree=ui->degree_->text();
        point=ui->point_->text();
        Sine<TComplex> sine_object(degree.toInt());
        ss<<point.toStdString();
        TComplex ar;
        ss>>ar;
        iss<<sine_object.solve_for_x(ar);
        std::string t;
        iss>>t;
        int x_=std::stoi(t);
        ui->result_->setText(QString::fromStdString(t));
        qDebug()<<t;

        showDrawingWindow(degree.toInt(), 0);

        /*QPainter painter(this);

        painter.setPen(Qt::blue);
        double x1=0, y1, x2, y2;
        std::stringstream ss_;
        ar = double(0);
        ss_<<sine_object.solve_for_x(ar);
        ss_>>t;
        y1=std::stoi(t);


        for(double i=0.001; i<50; i+=0.001){
            std::stringstream ss_;
            ar = double(i);
            ss_<<sine_object.solve_for_x(ar);
            std::string t;
            ss_>>t;
            y2=std::stoi(t);
            painter.drawLine(x1,y1,i,y2);
            x1=x2;
            y1=y2;
        }*/
    }

    if(ui->si_->isChecked()){
        degree=ui->degree_->text();
        point=ui->point_->text();
        SineIntegral<TComplex> sineIntegral_object(degree.toInt());
        ss<<point.toStdString();
        TComplex ar;
        ss>>ar;
        iss<<sineIntegral_object.solve_for_x(ar);
        std::string t;
        iss>>t;
        ui->result_->setText(QString::fromStdString(t));

        qDebug()<<t;
        showDrawingWindow(degree.toInt(), 1);

    }
}

void  MainWindow ::showDrawingWindow(int deg,bool s) {
    DrawingWindow *drawingWindow = new DrawingWindow(deg, s);
    drawingWindow->show();
}



