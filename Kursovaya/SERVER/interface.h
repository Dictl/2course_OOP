#ifndef INTERFACE_H
#define INTERFACE_H
#include <QMainWindow>
#include <QUdpSocket>
#include <sstream>
//#include "abonent.h"
#include "clients.h"
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int argc, char *argv[],QWidget *parent = nullptr);
    ~MainWindow();
    //Abonent *client;
public slots:
    void active();
   // void getAbonentData(QString &message);

private slots:

    void on_pushButton1_clicked();

private:
    int _argc;

    Ui::MainWindow *ui;
    QByteArray data;
    char **_argv;

};
#endif // INTERFACE_H
