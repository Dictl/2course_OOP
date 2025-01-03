#ifndef CLIENT_H
#define CLIENT_H
#include <QCloseEvent>
#include <QWidget>
#include <QStringListModel>
namespace Ui {
class Clients;
}

class Clients : public QWidget
{
    Q_OBJECT

public:
    explicit Clients(QWidget *parent = nullptr);
    ~Clients();
signals:
    void clDestroyed();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::Clients *ui;
    QStringListModel *model;
public slots:
    void newDataRecieved(QVector<std::pair<quint16, int>> v, QVector<std::pair<quint16, quint16>> c, int maxAb, int maxCon);
};

#endif // CLIENT_H
