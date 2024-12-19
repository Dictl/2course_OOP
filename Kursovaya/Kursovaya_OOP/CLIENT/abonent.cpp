#include "abonent.h"

Abonent::Abonent() {
    comm = new Communicator(QHostAddress(NETWORK_IP), 1);
    connect(comm, &Communicator::messageRecieved, this, &Abonent::handleMessage);
    comm->sendToAddress("0", NETWORK_IP, SERVER_PORT);
    qDebug() << "Creation request have been sent. Processing...";
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
        itfMesSs << "New Abonent created at port: " << id;
        qDebug() << "I was born at port"<< id;
        idNumber = id;
        status = 0;
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
    QString toInterface = QString::fromStdString(itfMesSs.str());
    emit transferToInteface(toInterface);
}
