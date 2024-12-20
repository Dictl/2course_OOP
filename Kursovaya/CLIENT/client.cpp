#include "client.h"
#include "ui_client.h"



client::client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::client)
{
    me= new Abonent();
    connect(me,&Abonent::transferToInteface,this,&client::dataOut);
    connect(me,&Abonent::transferToInteface,this,&client::dataIn);
    ui->setupUi(this);
    ui->result->setEnabled(false);
    QIcon icon1(":call.png");
    QIcon icon2(":unnamed.png");
    ui->call->setIcon(icon1);
    ui->call_->setIcon(icon2);

}

client::~client()
{
    delete ui;
    delete me;
}

void client::dataIn(QString s)
{
    std::stringstream rReqSs;
    rReqSs << s.QString::toStdString();
    int requestType;
    rReqSs >> requestType;
    switch (requestType) {

    case 0: // abonent recieved an ID (port)
        quint16 id;
        rReqSs >> id;
        setWindowTitle(QString::number(me->getNumber()));
        ui->call->setEnabled(false);
        ui->call_->setEnabled(false);
        ui->result->setText(QString("Not ready"));
    break; // so a new abonent is born under a "phone number" which is just 5 digit port

    case 1: // abonent asked for ATS status (is connection limit reached?) and recieved an answer
        bool atsFull;
        rReqSs >> atsFull;
        if (!atsFull){
            ui->message->insertPlainText("\nReady to call!");
            ui->call->setEnabled(true);
            ui->result->setText(QString("Ready"));
            ui->result->setStyleSheet("QLineEdit {background-color: cyan;}");
            ui->number->setEnabled(true);
        }
        else{
            ui->message->insertPlainText("\nATS is busy!");
            ui->call->setEnabled(false);
            ui->result->setText(QString("Busy"));
            ui->result->setStyleSheet("QLineEdit {background-color: red;}");
        }
    break;

    case 2:
        // status = 0;
        ui->message->insertPlainText("\nCall is rejected or aborted");
        ui->checkATS->setEnabled(true);
        ui->call->setEnabled(false);
        ui->result->setText(QString("Not ready"));
        ui->result->setStyleSheet("QLineEdit {background-color: white;}");
        ui->call_->setEnabled(false);

    break;

    case 3:{
        // status = 3; this client is being called and the caller
        quint16 caller;
        ui->number->setEnabled(false);
        rReqSs >> caller;
        ui->message->insertPlainText("\n"+QString::number(caller) + " is calling you!");
        ui->result->setText(QString("Calling"));
        ui->result->setStyleSheet("QLineEdit {background-color: yellow;}");
        ui->checkATS->setEnabled(false);
        ui->call->setEnabled(true);
        ui->call_->setEnabled(true);
        inCallWith = caller;
    break;}

    case 4:
        // status = 4; the two are in a call
        ui->call->setEnabled(false);
        ui->call_->setEnabled(true);
        ui->message->insertPlainText("\nConnection is established!");
        ui->result->setStyleSheet("QLineEdit {background-color: lime;}");
        ui->result->setText(QString("Connected"));
    break;

    case 5:{
        quint16 sender;
        rReqSs >> sender;
        std::string str = rReqSs.str();
        std::regex regex_pattern(R"((?:\d+\s+){2})");
        std::string result = std::regex_replace(str, regex_pattern, "");
        ui->message->insertPlainText("\n["+QString::number(sender)+"]["+QTime::currentTime().toString()+"]: "+QString::fromStdString(result));
    break;}

    case 6:{
        ui->call_->setEnabled(false);
        ui->number->setEnabled(true);
        ui->checkATS->setEnabled(true);
        ui->message->insertPlainText("\nCall is over!");
        ui->result->setText(QString("Not ready"));
        ui->result->setStyleSheet("QLineEdit {background-color: white;}");
        QTextCursor cursor = ui->message->textCursor();
        break;}

    case 7: // Prohibiting server responses (number does not exist, answer the call first ETC
        me->setStatus(2);
        ui->call->setEnabled(false);
        ui->call_->setEnabled(false);
        ui->result->setText(QString("Not ready"));
        ui->checkATS->setEnabled(true);
        ui->number->setEnabled(true);
        ui->result->setStyleSheet("QLineEdit {background-color: white;}");
        std::string str = rReqSs.str();
        std::regex regex_pattern(R"((?:\d+\s+){1})");
        std::string result = std::regex_replace(str, regex_pattern, "");
        ui->message->insertPlainText("\n[SERVER]["+QTime::currentTime().toString()+"]: "+QString::fromStdString(result));
    break;
    }
    QTextCursor cursor = ui->message->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->message->setTextCursor(cursor);
}
void client::dataOut(QString s){
    qDebug()<<s;
}

void client::on_checkATS_clicked()
{
    me->pickUp();
}


void client::on_textToSend_returnPressed() {
    if (me->getStatus() == 4){
        if (ui->textToSend->text().QString::trimmed() == ""){
            ui->textToSend->clear();
            return;
        }
        QString textToTransfer = "5 " + QString::number(me->getNumber()) + " " + ui->textToSend->text();
        ui->message->insertPlainText("\n[You][" + QTime::currentTime().toString()+"]: " + ui->textToSend->text());
        ui->textToSend->clear();
        me->sendMessage(textToTransfer);
        QTextCursor cursor = ui->message->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->message->setTextCursor(cursor);
    }
}


void client::on_call_clicked() {

    switch (me->getStatus()){

    case 1:{
        if (ui->number->text().QString::trimmed() == "") {
            ui->number->clear();
            return;
        }
        std::stringstream ss;
        ss << ui->number->text().QString::toStdString();
        quint16 addressee;
        if (ss >> addressee) {
            if (addressee == me->getNumber()){
                ui->message->insertPlainText("\nYou can't call yourself!");
                ui->number->clear();
                QTextCursor cursor = ui->message->textCursor();
                cursor.movePosition(QTextCursor::End);
                ui->message->setTextCursor(cursor);
                return;
            }
            ui->number->setEnabled(false);
            inCallWith = addressee;
            ui->number->clear();
            ui->message->insertPlainText("\nYou're calling " + QString::number(addressee));
            ui->result->setText(QString("Calling"));
            ui->result->setStyleSheet("QLineEdit {background-color: yellow;}");
            ui->checkATS->setEnabled(false);
            ui->call_->setEnabled(true);
            ui->call->setEnabled(false);
            me->call(addressee);
        }
        else{
            ui->message->insertPlainText("\nError reading a number!");
        }
    break;}

    case 3:{
        ui->result->setText(QString("Connected"));
        ui->result->setStyleSheet("QLineEdit {background-color: lime;}");
        me->answer(inCallWith);
    break;}

    }
    QTextCursor cursor = ui->message->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->message->setTextCursor(cursor);
}


void client::on_call__clicked() {
    switch (me->getStatus()){

    case 3:{
        ui->result->setText(QString("Not ready"));
        ui->message->insertPlainText("\nCall is rejected or aborted");
        ui->result->setStyleSheet("QLineEdit {background-color: white;}");
        ui->call->setEnabled(false);
        ui->call_->setEnabled(false);
        ui->checkATS->setEnabled(true);
        ui->number->setEnabled(true);
    break;}

    case 4:{
        ui->result->setText(QString("Not ready"));
        ui->result->setStyleSheet("QLineEdit {background-color: white;}");
        ui->call->setEnabled(false);
        ui->call_->setEnabled(false);
        ui->checkATS->setEnabled(true);
        ui->number->setEnabled(true);
    break;}

    }
    me->hangUp(inCallWith);
    QTextCursor cursor = ui->message->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->message->setTextCursor(cursor);
}

