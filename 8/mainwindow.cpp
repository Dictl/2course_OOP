#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "function.h"
#include "array.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QIntValidator>

QString degree, point, from, before;

Array<TComplex> arr_object;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QIntValidator *les = new QIntValidator(0,100000,0);
    ui->degree_->setValidator(les);
    ui->sin_->setChecked(true);
    //ui->from_->setValidator(les);
    //ui->before_->setValidator(les);

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
        from=ui->from_->text();
        before=ui->before_->text();
        Sine<TComplex> sine_object(degree.toInt()*2);
        ss<<point.toStdString();
        TComplex ar;
        ss>>ar;
        iss<<sine_object.solve_for_x(ar);
        std::string t;
        iss>>t;
        int x_=std::stoi(t);
        ui->result_->setText(QString::fromStdString(t));
        qDebug()<<t;

        showDrawingWindow(degree.toInt(), 0, from.toInt(), before.toInt());
    }

    if(ui->si_->isChecked()){
        degree=ui->degree_->text();
        point=ui->point_->text();
        from=ui->from_->text();
        before=ui->before_->text();
        SineIntegral<TComplex> sineIntegral_object(degree.toInt()*2);
        ss<<point.toStdString();
        TComplex ar;
        ss>>ar;
        iss<<sineIntegral_object.solve_for_x(ar);
        std::string t;
        iss>>t;
        ui->result_->setText(QString::fromStdString(t));

        qDebug()<<t;
        showDrawingWindow(degree.toInt(), 1, from.toInt(), before.toInt());

    }
}

void  MainWindow ::showDrawingWindow(int deg,bool s, int f, int b) {
    DrawingWindow *drawingWindow = new DrawingWindow(deg, s, f, b );
    drawingWindow->show();
}



