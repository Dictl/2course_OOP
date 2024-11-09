#include "interface.h"
#include "ui_interface.h"
#include "array.h"
#include <limits>
#include "polynom.h"
#include <sstream>

QString cof_a, n_counts, str, counter, point_x, cof_a2, n, nom, root;
Array *arr_object;
stringstream iss;
Polynom *poly_object = new Polynom(3);
Array *roots_object = new Array;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    iss <<"3+0i\n4+0i\n6+0i\n8-6i\n";
    iss >> *poly_object;
    ui->setupUi(this);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->line_counter->setVisible(false);
    ui->line_root->setVisible(false);
    ui->line_cof_a->setVisible(false);
    ui->line_index_root->setVisible(false);
    ui->line_value->setVisible(false);
    ui->line_x->setVisible(false);
    ui->line_size->setVisible(false);
    ui->line_cof_a_2->setVisible(false);
    ui->lineEdit->setReadOnly(true);
    ui->text->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_polynom_n_clicked()
{
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->line_counter->setVisible(true);
    ui->line_root->setVisible(true);
    ui->line_cof_a->setVisible(true);
    ui->line_index_root->setVisible(false);
    ui->line_value->setVisible(false);
    ui->line_x->setVisible(false);
    ui->line_size->setVisible(false);
    ui->line_cof_a_2->setVisible(false);
    ui->lineEdit->clear();
    ui->text->clear();
}


void MainWindow::on_resize_cof_clicked()
{
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->line_counter->setVisible(false);
    ui->line_root->setVisible(false);
    ui->line_cof_a->setVisible(false);
    ui->line_index_root->setVisible(false);
    ui->line_value->setVisible(false);
    ui->line_x->setVisible(false);
    ui->line_size->setVisible(true);
    ui->line_cof_a_2->setVisible(false);
    ui->lineEdit->clear();
    ui->text->clear();
}


void MainWindow::on_polynom_x_clicked()
{
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->line_counter->setVisible(false);
    ui->line_root->setVisible(false);
    ui->line_cof_a->setVisible(false);
    ui->line_index_root->setVisible(false);
    ui->line_value->setVisible(false);
    ui->line_x->setVisible(true);
    ui->line_size->setVisible(false);
    ui->line_cof_a_2->setVisible(false);
    ui->lineEdit->clear();
    ui->text->clear();
}


void MainWindow::on_change_cof_a_clicked()
{
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->line_counter->setVisible(false);
    ui->line_root->setVisible(false);
    ui->line_cof_a->setVisible(false);
    ui->line_index_root->setVisible(false);
    ui->line_value->setVisible(false);
    ui->line_x->setVisible(false);
    ui->line_size->setVisible(false);
    ui->line_cof_a_2->setVisible(true);
    ui->lineEdit->clear();
    ui->text->clear();
}


void MainWindow::on_change_roots_clicked()
{
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->line_counter->setVisible(false);
    ui->line_root->setVisible(false);
    ui->line_cof_a->setVisible(false);
    ui->line_index_root->setVisible(true);
    ui->line_value->setVisible(true);
    ui->line_x->setVisible(false);
    ui->line_size->setVisible(false);
    ui->line_cof_a_2->setVisible(false);
    ui->lineEdit->clear();
    ui->text->clear();
}


void MainWindow::on_polynom_1_clicked()
{
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->line_counter->setVisible(false);
    ui->line_root->setVisible(false);
    ui->line_cof_a->setVisible(false);
    ui->line_index_root->setVisible(false);
    ui->line_value->setVisible(false);
    ui->line_x->setVisible(false);
    ui->line_size->setVisible(false);
    ui->line_cof_a_2->setVisible(false);
    ui->text->setText("Полином 1-го вида");
    poly_object->set_display_format(0);
    stringstream ss;
    ss << *poly_object;
    ui->lineEdit->setText(QString::fromStdString(ss.str()));
}


void MainWindow::on_polynom_2_clicked()
{
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->line_counter->setVisible(false);
    ui->line_root->setVisible(false);
    ui->line_cof_a->setVisible(false);
    ui->line_index_root->setVisible(false);
    ui->line_value->setVisible(false);
    ui->line_x->setVisible(false);
    ui->line_size->setVisible(false);
    ui->line_cof_a_2->setVisible(false);
    ui->text->setText("Полином 2-го вида");
    poly_object->set_display_format(1);
    stringstream ss;
    ss << *poly_object;
    ui->lineEdit->setText(QString::fromStdString(ss.str()));
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->polynom_n->isChecked()) {
        counter = ui->line_counter->text();
        if(counter.toStdString()=="0"){
            poly_object = new Polynom();
            cout << *poly_object<<endl;}
        else {
            poly_object= new Polynom(size_t(counter.toInt()));
            cof_a = ui->line_cof_a->text();
            iss<<cof_a.toStdString()<<endl;
            n_counts = ui->line_root->text();
            iss<<n_counts.toStdString()<<endl;
            iss >> *poly_object;
        }
    }
    if (ui->polynom_x->isChecked()) {
        point_x = ui->line_x->text();
        stringstream ss;
        ss<< point_x.toStdString() ;
        number t;
        ss>>t;
        t = poly_object->solve_for_x(t);
        stringstream ssa;
        ss.str();
        ssa<<t;
        ui->lineEdit->clear();
        ui->lineEdit->show();
        ui->lineEdit->setText(QString::fromStdString(ssa.str()));
    }
    if (ui->change_cof_a->isChecked()) {
        cof_a2=ui->line_cof_a_2->text();
        stringstream ss;
        ss<<cof_a2.toStdString();
        number t;
        ss>>t;
        poly_object->set_a_n(t);
    }
    if (ui->resize_cof->isChecked()) {
        n=ui->line_size->text();
        poly_object->resize(n.toInt());
    }
    if (ui->change_roots->isChecked()) {
        nom=ui->line_index_root->text();;
        root=ui->line_value->text();
        stringstream ss;
        ss<<root.toStdString();
        number t;
        ss>>t;
        poly_object->change_root(nom.toInt(), t);
    }


}

