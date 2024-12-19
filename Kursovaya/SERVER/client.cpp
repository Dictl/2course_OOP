#include "client.h"
#include "ui_client.h"

clients::clients(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::clients)
{
    ui->setupUi(this);
}

clients::~clients()
{
    delete ui;
}
void clients::closeEvent(QCloseEvent *event){
    emit clDestroyed();
    event->accept();
}
void clients::on_pushButton_clicked()
{

    /*client *my_client = new client(nullptr);
    my_client->setWindowTitle("1");
    my_client->show();*/
}



