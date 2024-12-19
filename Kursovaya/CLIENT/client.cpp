#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
    ui->result->setEnabled(false);
    QIcon icon1(":call.png");
    QIcon icon2(":unnamed.png");
    ui->call->setIcon(icon1);
    ui->call_->setIcon(icon2);
}

client::~client()
{
    delete ui;
}
