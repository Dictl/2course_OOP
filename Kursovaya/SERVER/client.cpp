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
    if (model != nullptr) delete model;
}
void Clients::closeEvent(QCloseEvent *event){
    emit clDestroyed();
    event->accept();
}
void Clients::newDataRecieved(QVector<std::pair<quint16, int>> v, QVector<std::pair<quint16, quint16>> c) {
    QStringList list;
    if (v.size() != 0){
        list << QString("Connected abonents (" + QString::number(v.size()) + "):");
        for (std::pair<quint16, int> pair : v){
            list << QString("Number: " + QString::number(pair.first) + " Status: " + QString::number(pair.second));
        }
    }
    if (c.size() != 0){
        list << QString("Current calls (" + QString::number(c.size()) + "):");
        for (std::pair<quint16, quint16> pair : c){
            list << QString("{" + QString::number(pair.first) + "," + QString::number(pair.second) + "}");
        }
    }
    model = new QStringListModel(list);
    ui->list_clients->setModel(model);

}



