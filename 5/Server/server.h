#ifndef SERVER_H
#define SERVER_H
#include "polynom.h"
#include "qcoreapplication.h"
#include "sstream"
#include <communicator.h>
#include <QUdpSocket>

class Server : public QCoreApplication
{
    Q_OBJECT
public:
    Server(int, char**);
    ~Server();
private:
    Communicator *comm;
    Polynom *poly;
    /*We store it on server, yes. This way, we can make a default polynomial.
     Also, we have to carry over the amount of the roots polynomial has in
     order to prevent it from displaying when some index in *poly->roots
     is actually blank.*/
public slots:
    void handleMessage(QString &message);
};

#endif // SERVER_H
