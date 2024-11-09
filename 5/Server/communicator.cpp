#include "communicator.h"

Communicator::Communicator() {
    socket = new QUdpSocket(this);
}
Communicator::Communicator(QHostAddress address, quint16 port) : Communicator() {
    socket->bind(address, port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
}
void Communicator::sendToAddress(QString request, QHostAddress address, quint16 port) {
        socket->writeDatagram(request.toUtf8(), address, port);
}
void Communicator::slotReadyRead()
{
    QHostAddress sender;
    quint16 senderPort;
    QString response; // recieved request stringstream
    qDebug() << "reading";
    while (socket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(),datagram.size(),&sender,&senderPort);
        response = QString(datagram);
    }
    emit messageRecieved(response);
}

