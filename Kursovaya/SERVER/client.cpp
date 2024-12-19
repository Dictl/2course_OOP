#include "client.h"
#include "ui_client.h"

Clients::Clients(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Clients)
{
    ui->setupUi(this);
}

Clients::~Clients()
{
    delete ui;
}
void Clients::closeEvent(QCloseEvent *event){
    emit clDestroyed();
    event->accept();
}
void Clients::on_pushButton_clicked()
{

    /*client *my_client = new client(nullptr);
    my_client->setWindowTitle("1");
    my_client->show();*/
}



