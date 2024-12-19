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
    void sendToServer(QString &message);
private:
    Communicator *comm;
    quint16 idNumber;
    short status = 1;
public slots:
    void handleMessage(QString &message);
signals:
    void transferToInteface(QString &deciphered_message);
};

#endif // ABONENT_H
