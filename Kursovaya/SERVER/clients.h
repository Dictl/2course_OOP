#ifndef CLIENTS_H
#define CLIENTS_H
#include <QCloseEvent>
#include <QWidget>
#include <QApplication>
namespace Ui {
class cluents;
}

class cluents : public QWidget
{
    Q_OBJECT

public:
    explicit cluents(QWidget *parent = nullptr);
    ~cluents();

private slots:
    void on_pushButton_clicked();

signals:
    void clDestroyed();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::cluents *ui;
};

#endif // CLIENTS_H
