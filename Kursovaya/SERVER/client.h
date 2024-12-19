#ifndef CLIENT_H
#define CLIENT_H
#include <QCloseEvent>
#include <QWidget>
namespace Ui {
class clients;
}

class clients : public QWidget
{
    Q_OBJECT

public:
    explicit clients(QWidget *parent = nullptr);
    ~clients();

private slots:
    void on_pushButton_clicked();

signals:
    void clDestroyed();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::clients *ui;
};

#endif // CLIENT_H
