#include "server.h"

Server::Server(int argc, char *argv[]) : QCoreApplication(argc, argv){
    comm = new Communicator(QHostAddress("127.0.0.1"), 1984);
    connect(comm, &Communicator::messageRecieved, this, &Server::handleMessage);
    this->poly=new Polynom(3);
    stringstream fp;
    fp << "1+0i 2+0i 3+0i 4+0i";
    fp >> *poly;
    qDebug() << "start";
}
Server::~Server(){
    delete poly;
}
void Server::handleMessage(QString &message){
    QHostAddress addressee = QHostAddress("127.0.0.1");
    quint16 addresseePort = 1985;
    stringstream rReqSs, resSs; // recieved request stringstream
    qDebug() << "чтение";
    rReqSs << message.toStdString();
    int menu_number;
    rReqSs >> menu_number;
    qDebug() << "Полученный:";
    switch (menu_number) {
    case 1:{
    int new_poly_size;
    qDebug() << "1:Запрос на создание нового полинома.";
    if (rReqSs >> new_poly_size || !rReqSs.fail()){
        qDebug() << "Размер:" << new_poly_size;
        if (new_poly_size <= 0) {
            comm->sendToAddress("0", addressee, addresseePort); //if it's a zero polynomial
            return;
        }
        stringstream check;
        string current_root;
        int root_counter = 0;
        check.str(rReqSs.str());     // <==== a copy of rReqSs to check roots. BUT!
        string *dummy = new string; // rReqSs has a menu number and a number of roots
        check >> *dummy;           // in first two iterations. So we extract the first
        check >> *dummy;          // two in dummy and get rid of it.
        delete dummy;            // This way, we get an ss of roots ONLY. Profit!
        while (!check.eof()){
            if (check >> current_root || !check.fail()){
                root_counter++;

            }
            else{
                comm->sendToAddress("Ошибка при анализе данных из запроса!", addressee, addresseePort);
                qDebug() << "Ошибка при разборе данных из запроса! Данные:"
                         << message;
                return;
            }
        }
        if (root_counter - 1 < new_poly_size) {
            comm->sendToAddress("Ожидалось больше корней, чем предоставлено", addressee, addresseePort);
            qDebug() << "Недостаточно корней для создания полинома. Данные:"
                     << message;
            return;
            /*we HAVE TO do this separately or else it
            goes copying the only root to all indexes which is nuts*/
        }
        this->poly = new Polynom(new_poly_size);
        rReqSs >> *poly; // and finally we can create a polynomial
        resSs << "Созданный полином: " << *poly;
        comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
        qDebug() << "Полином успешно отправлен.";
        qDebug() << "Отправленный полином:" << resSs.str();
        return;
    }
    else {
        comm->sendToAddress("Ошибка при анализе данных!", addressee, addresseePort);
        qDebug() << "Ошибка при разборе данных из запроса! Данные:"
                 << message;
        return;
    }
    break;}
    case 2:
    {
        qDebug() << "2: Запрос на изменение размера полинома.";
        int new_roots_size = 0;
        if(rReqSs >> new_roots_size || !rReqSs.fail()){
            poly->resize(new_roots_size);
            comm->sendToAddress("Массив корней был успешно изменен", addressee, addresseePort);
            qDebug() << "Массив корней был успешно изменен";
            return;
        }
        else{
            comm->sendToAddress("Ошибка при анализе данных!", addressee, addresseePort);
            qDebug() << "Ошибка при разборе данных из запроса! Данные:"
                     << message;
            return;
        }
        break;}
    case 3:
    {
        qDebug() << "3:Запрос на расчет значения в x.";
        number x;
        if(rReqSs >> x || !rReqSs.fail()){
            resSs << poly->solve_for_x(x);
            comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
            qDebug() << "Результат в x успешно отправлен.";
            qDebug() << "Отправлено результат:" << resSs.str();
            return;
        }
        else{
            comm->sendToAddress("Ошибка при анализе данных!", addressee, addresseePort);
            qDebug() << "Ошибка при разборе данных из запроса! Данные:"
                     << message;
            return;
        }
        break;}
    case 4:
    {
        qDebug() << "4:Запрос на изменение значения A_n.";
        number new_a_n;
        if(rReqSs >> new_a_n || !rReqSs.fail()){
            poly->set_a_n(new_a_n);
            resSs << new_a_n;
            comm->sendToAddress("Коэффициент A_n был изменен на: " + QString::fromStdString(resSs.str()), addressee, addresseePort);
            qDebug() << "Коэффициент A_n успешно изменен.";
            return;
        }
        else{
            comm->sendToAddress("Ошибка при анализе данных!", addressee, addresseePort);
            qDebug() << "Ошибка при разборе данных из запроса! Данные:"
                     << message;
            return;
        }
        break;}
    case 5:
    {
        qDebug() << "5:Запрос на изменение определенного корня.";
        int index;
        number new_root;
        if(rReqSs >> index || !rReqSs.fail()){
            if(rReqSs >> new_root || !rReqSs.fail()){
                poly->change_root(index,new_root);
                comm->sendToAddress("Корень успешно изменен!", addressee, addresseePort);
                qDebug() << "Корень успешно изменен.";
                return;
            }
            else{
                comm->sendToAddress("Ошибка при анализе данных!", addressee, addresseePort);
                qDebug() << "Ошибка при разборе данных из запроса! Данные:"
                         << message;
                return;
            }
        }
        else {
            comm->sendToAddress("Ошибка при анализе данных!", addressee, addresseePort);
            qDebug() << "Ошибка при разборе данных из запроса! Данные:"
                     << message;
            return;
        }
        break;}
    case 6:{
        qDebug() << "6:Запрос на отображение полинома в неразвернутом виде.";
        int index; // I want at least some clarity. Let this store the missing index if there is one due to resize.
        index = poly->are_roots_full();
        if (index == -1){
            poly->set_display_format(0);
            resSs << *poly;
            comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
            qDebug() << "Полином был успешно отправлен. Отправлено:" << QString::fromStdString(resSs.str());
            return;
        }
        else{
            resSs<<index;
            comm->sendToAddress("Один или несколько индексов пусты. Первый встреченный пустой индекс: " + QString::fromStdString(resSs.str()), addressee, addresseePort);
            qDebug() << "Один или несколько индексов пусты. Операция прервана.";
        }
        break;}
    case 7:
        qDebug() << "7:Запрос на отображение полинома в неразвернутом виде.";
        int index;
        index = poly->are_roots_full();
        if (index == -1){
            poly->set_display_format(1);
            resSs << *poly;
            comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
            qDebug() << "Полином был успешно отправлен. Отправлено:" << QString::fromStdString(resSs.str());
            return;
        }
        else{
            resSs<<index;
            comm->sendToAddress("Один или несколько индексов пусты. Первый встреченный пустой индекс: " + QString::fromStdString(resSs.str()), addressee, addresseePort);
            qDebug() << "Один или несколько индексов пусты. Операция прервана.";
        }
        break;
    }
}
