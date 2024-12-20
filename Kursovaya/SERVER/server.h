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
    int maximumConnections, currentConnections, maximumAbonents, currentAbonents;
    Communicator *comm;
    QVector<quint16> *freeIDs;
    QVector<std::pair<quint16, int>> *takenIDs;
    QVector<std::pair<quint16, quint16>> connections;
    void messageToAbonent(std::string message, quint16 sender);
    void connectAbonents(quint16 ab1, quint16 ab2);
    void disconnectAbonents(quint16 anyOfTheTwo);
    void ping(quint16 whoPinged);
public slots:
    void handleMessage(QString &message);
signals:
    void messageNotice(QVector<std::pair<quint16, int>>, QVector<std::pair<quint16, quint16>>, int, int);
};
int indexFind(QVector<std::pair<quint16, quint16>> v, int key);
int indexFind(QVector<std::pair<quint16, int>> v, int key);
void updateValue(QVector<std::pair<quint16, int>>& takenIDs, quint16 searchKey, int newValue);
#endif // SERVER_H
