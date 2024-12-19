#include "clients.h"
#include "ui_clients.h"

cluents::cluents(QWidget *parent)
    : QWidget(this)
    , ui(new Ui::cluents)
{
    ui->setupUi(this);
}

cluents::~cluents()
{

    delete ui;


}
void cluents::closeEvent(QCloseEvent *event){
    emit clDestroyed();
    event->accept();
}
void cluents::on_pushButton_clicked()
{        

    /*client *my_client = new client(nullptr);
    my_client->setWindowTitle("1");
    my_client->show();*/
}



