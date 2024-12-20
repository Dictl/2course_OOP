#include "client.h"
#include "ui_client.h"


client::client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::client)
{


    me= new Abonent();
    connect(me,&Abonent::transferToInteface,this,&client::dataOut);
    ui->setupUi(this);

    ui->result->setEnabled(false);
    QIcon icon1(":call.png");
    QIcon icon2(":unnamed.png");
    ui->call->setIcon(icon1);
    ui->call_->setIcon(icon2);
    QString s = "1 65513";
    me->sendToServer(s);
    setWindowTitle(QString::number(me->getNumber()));

}

client::~client()
{
    delete ui;
}
client::dataOut(QString s){
    qDebug()<<s;

}
