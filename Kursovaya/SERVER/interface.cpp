#include "interface.h"
#include "ui_interface.h"
#include <QButtonGroup>
#include <sstream>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QIntValidator>
#include "server.h"


using namespace std;
stringstream req_ss, res_ss; //request and response stringstream
QString limit, n_abonent;


MainWindow::MainWindow(int argc, char *argv[],QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //client = new Abonent()
    ui->setupUi(this);
    _argc = argc;
    _argv = argv;
    QIntValidator *les = new QIntValidator(0,10000,this);
    ui->n_abonent_->setValidator(les);
    ui->limit_connect->setValidator(les);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::active(){
    ui->n_abonent_->setEnabled(true);
    ui->limit_connect->setEnabled(true);
    ui->pushButton1->setEnabled(true);
}
void MainWindow::on_pushButton1_clicked()
{
    n_abonent=ui->n_abonent_->text();
    limit=ui->limit_connect->text();
    Server server(limit.toInt(), n_abonent.toInt());
    my_clients = new Clients();
    my_clients->show();
    connect(my_clients, &Clients::clDestroyed, this, &MainWindow::active);
    ui->n_abonent_->setEnabled(false);
    ui->limit_connect->setEnabled(false);
    ui->pushButton1->setEnabled(false);
}


