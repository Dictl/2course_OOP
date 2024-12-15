#include <sstream>
#include "interface.h"
#include "ui_interface.h"
#include <QButtonGroup>

using namespace std;
QString cof_a, n_counts, str, counter, point_x, cof_a2, n, nom, root;
stringstream req_ss, res_ss; //request and response stringstream


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    client = new Abonent();
    connect(client, &Abonent::transferToInteface, this, &MainWindow::getAbonentData);
    ui->setupUi(this);
    QButtonGroup *group1 = new QButtonGroup(this);
    QButtonGroup *group2 = new QButtonGroup(this);
    group1->addButton(ui->real_button);
    group1->addButton(ui->complex_button);
    group2->addButton(ui->polynom_n);
    group2->addButton(ui->polynom_x);
    group2->addButton(ui->polynom_1);
    group2->addButton(ui->polynom_2);
    group2->addButton(ui->resize_cof);
    group2->addButton(ui->change_cof_a);
    group2->addButton(ui->change_roots);
    ui->real_button->click();
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


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getAbonentData(QString &message)
{
    ui->lineEdit->setText(message);
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
}


void MainWindow::on_pushButton_clicked()
{
    req_ss.str(std::string());
    if (ui->polynom_n->isChecked()) {
        cof_a = ui->line_cof_a->text();
        req_ss << cof_a.QString::toStdString();
    }
    if (ui->polynom_x->isChecked()) {
        req_ss << "3 ";
        point_x = ui->line_x->text();
        req_ss<< point_x.toStdString();
    }
    if (ui->change_cof_a->isChecked()) {
        req_ss << "4 ";
        cof_a2=ui->line_cof_a_2->text();
        req_ss<<cof_a2.toStdString();
    }
    if (ui->resize_cof->isChecked()) {
        req_ss << "2 ";
        n=ui->line_size->text();
        req_ss<<n.toStdString();
    }
    if (ui->change_roots->isChecked()) {
        req_ss << "5 ";
        nom=ui->line_index_root->text();
        root=ui->line_value->text();
        req_ss<<nom.toStdString() << " " << root.toStdString();
    }
    if (ui->polynom_1->isChecked()) {
        req_ss << "6";
    }
    if (ui->polynom_2->isChecked()) {
        req_ss << "7";
    }
    qDebug() << QString::fromStdString(req_ss.str());
    QString a = QString::fromStdString(req_ss.str());
    if (req_ss.str() == "0 " || req_ss.str() == "1 ") return;
    client->sendToServer(a);


}


