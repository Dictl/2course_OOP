#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include "abonent.h"
#include "QTime"

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
    void dataIn(QString s);
    void dataOut(QString s);
private slots:
    void on_checkATS_clicked();

    void on_textToSend_returnPressed();

    void on_call_clicked();

    void on_call__clicked();

private:
    quint16 inCallWith;
    Ui::client *ui;
    Abonent *me;

};

#endif // CLIENT_H

