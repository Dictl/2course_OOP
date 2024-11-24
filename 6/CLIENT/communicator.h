#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include <QUdpSocket>

class Communicator : public QObject
{
    Q_OBJECT
public:
    Communicator();
    Communicator(QHostAddress address, quint16 port);
    void sendToAddress(QString request, QHostAddress address, quint16 port);

private:
    QUdpSocket* socket;
public slots:
    void slotReadyRead();
signals:
    void messageRecieved(QString &deciphered_message);
};

#endif // COMMUNICATOR_H
