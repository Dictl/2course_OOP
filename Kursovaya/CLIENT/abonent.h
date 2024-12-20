#ifndef ABONENT_H
#define ABONENT_H
#include "communicator.h"
#include <sstream>
#include <regex>

#define NETWORK_IP QHostAddress("127.0.0.1")
#define SERVER_PORT (quint16) 1984

class Abonent : public QObject
{
    Q_OBJECT
public:
    Abonent();
    ~Abonent();
    quint16 getNumber();
    short getStatus();
    void call(quint16 number);
    void answer(quint16 who);
    void hangUp(quint16 who);
    void pickUp();
    void sendMessage(QString message);
    void setStatus(short status_);
private:
    void sendToServer(QString &message);
    Communicator *comm;
    quint16 idNumber;
    short status;
public slots:
    void handleMessage(QString &message);
signals:
    void transferToInteface(QString &deciphered_message);
};

#endif // ABONENT_H
