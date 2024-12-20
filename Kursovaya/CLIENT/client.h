#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include "abonent.h"

namespace Ui {
class client;
}

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();
public slots:
    dataOut(QString s);
private:
    Ui::client *ui;
    Abonent *me;

};

#endif // CLIENT_H

