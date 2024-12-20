#include "abonent.h"
#include <sstream>
#include <regex>

Abonent::Abonent() {
    comm = new Communicator(QHostAddress(NETWORK_IP), 1);
    connect(comm, &Communicator::messageRecieved, this, &Abonent::handleMessage);
    comm->sendToAddress("0", NETWORK_IP, SERVER_PORT);
    qDebug() << "Creation request have been sent. Processing...";
}

Abonent::~Abonent()
{
    QString destruction = QString("7 "+QString::number(idNumber));
    sendToServer(destruction);
}

void Abonent::sendToServer(QString &message)
{
    comm->sendToAddress(message, NETWORK_IP, SERVER_PORT);
}

void Abonent::handleMessage(QString &message) {
    std::stringstream rReqSs, resSs, itfMesSs;
    qDebug() << "reading";
    rReqSs << message.toStdString();
    int requestType;
    rReqSs >> requestType;
    switch (requestType) {

    case 0: // abonent recieved an ID (port)
        delete comm; // out with the port 1
        quint16 id;
        rReqSs >> id;
        comm = new Communicator(QHostAddress(NETWORK_IP), id); // in with the new assigned port
        connect(comm, &Communicator::messageRecieved, this, &Abonent::handleMessage);
        idNumber = id;
        status = 0;
        itfMesSs << "0" << " ";
    break; // so a new abonent is born under a "phone number" which is just 5 digit port

    case 1: // abonent asked for ATS status (is connection limit reached?) and recieved an answer
        bool atsFull;
        rReqSs >> atsFull;
        !atsFull ? status = 1 : status = 2; // 1 = ready 2 = busy
        if (status == 1){
            itfMesSs << status << " Ready to call!";
        }
        else{
            itfMesSs << status << " ATS is busy!";
        }
    break;

    case 2:
        status = 0;
        itfMesSs << status << " Call is rejected!";
    break;

    case 3:{
        status = 3; // this client is being called
        quint16 caller;
        rReqSs >> caller;
        itfMesSs << status << " " << caller << " is calling you!";
    break;}

    case 4:
        status = 4; // the two are in a call
        itfMesSs << status << " Connection is established!";
    break;

    case 5:{
        quint16 sender;
        rReqSs >> sender;
        std::string str = rReqSs.str();
        std::regex regex_pattern(R"((?:\d+\s+){2})");
        std::string result = std::regex_replace(str, regex_pattern, "");
        itfMesSs << result;
    break;}

    case 6:
        status = 0;
        itfMesSs << status <<  " Call is over.";
    break;

    }
    emit transferToInteface(message);
}

quint16 Abonent::getNumber(){
    return idNumber;
}

short Abonent::getStatus() {
    return status;
}

void Abonent::call(quint16 number) {
    QString textToTransfer = "2 " + QString::number(idNumber) + " " + QString::number(number);
    sendToServer(textToTransfer);
    status = 3;
}

void Abonent::answer(quint16 who) {
    QString textToTransfer = "3 " + QString::number(idNumber) + " " + QString::number(who) + " 1";
    sendToServer(textToTransfer);
}

void Abonent::hangUp(quint16 who) {
    QString textToTransfer;
    switch(status)
    case 3:{
        textToTransfer = "3 " + QString::number(idNumber) + " " + QString::number(who) + " 0";
        break;
    case 4:
        textToTransfer = "6 " + QString::number(idNumber);
        break;
    }
    sendToServer(textToTransfer);
    status = 0;
}

void Abonent::pickUp() {
    QString message = QString("1 " + QString::number(idNumber));
    sendToServer(message);
}

void Abonent::sendMessage(QString message)
{
    sendToServer(message);
}

void Abonent::setStatus(short status_) {
    status = status_;
}
