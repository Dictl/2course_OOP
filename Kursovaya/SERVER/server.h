#ifndef SERVER_H
#define SERVER_H
#include "QApplication"
#include <sstream>
#include <communicator.h>
#include <bits/stdc++.h>

#define NETWORK_IP QHostAddress("127.0.0.1")
#define NEW_CLIENT_PORT (quint16) 1

class Server : public QObject
{
    Q_OBJECT
public:
    Server(int k, int n);
    ~Server();
private:
    int maximumConnections, currentConnections;
    Communicator *comm;
    std::vector<quint16> *freeIDs;
    std::vector<std::pair<quint16, quint16>> connections;

public slots:
    void handleMessage(QString &message);
};
int indexFind(std::vector<std::pair<quint16, quint16>> v, int key);
#endif // SERVER_H
