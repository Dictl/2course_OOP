#ifndef CLIENT_H
#define CLIENT_H
#include <QCloseEvent>
#include <QWidget>
namespace Ui {
class Clients;
}

class Clients : public QWidget
{
    Q_OBJECT

public:
    explicit Clients(QWidget *parent = nullptr);
    ~Clients();

private slots:
    void on_pushButton_clicked();

signals:
    void clDestroyed();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Clients *ui;
};

#endif // CLIENT_H
