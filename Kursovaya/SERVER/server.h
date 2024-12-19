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
    int maximumConnections, currentConnections, maximumAbonents, currentAbonents = 0;
    Communicator *comm;
    QVector<quint16> *freeIDs;
    QVector<std::pair<quint16, int>> *takenIDs;
    QVector<std::pair<quint16, quint16>> connections;

public slots:
    void handleMessage(QString &message);
signals:
    void messageNotice(QVector<std::pair<quint16, int>>, QVector<std::pair<quint16, quint16>>);
};
int indexFind(QVector<std::pair<quint16, quint16>> v, int key);
void updateValue(QVector<std::pair<quint16, int>>& takenIDs, quint16 searchKey, int newValue);
#endif // SERVER_H
