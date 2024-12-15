#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "function.h"
#include "array.h"
#include "sstream"
#include "sine.h"
#include "sineintegral.h"
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
        ui->result_->setText(QString::fromStdString(t));

        qDebug()<<t;
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

    }
}

