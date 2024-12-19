#include "server.h"

Server::Server(int k, int n) : QObject(){
    comm = new Communicator(QHostAddress("127.0.0.1"), 1984);
    connect(comm, &Communicator::messageRecieved, this, &Server::handleMessage);
    maximumAbonents = pow(2,n)-1;
    maximumConnections = pow(2,k);
    currentConnections = 0;
    freeIDs = new QVector<quint16>;
    takenIDs = new QVector<std::pair<quint16, int>>;
    for (quint16 i = 10000; i < pow(2,16)-1; i++){
        freeIDs->push_back(i);
    }
    qDebug() << "Start";
}
Server::~Server(){
    delete comm;
    delete freeIDs;
    delete takenIDs;
}
void Server::handleMessage(QString &message){
    std::stringstream rReqSs; // recieved request stringstream
    std::stringstream resSs; // response stringstream
    qDebug() << "reading";
    rReqSs << message.toStdString();
    int requestType;
    rReqSs >> requestType;
    qDebug() << "Recieved:";
    switch (requestType) {

        case 0:{ // Zero means a creation request, and it will assign an ID
            if(currentAbonents >= maximumAbonents) return;
            resSs << "0 ";
            resSs << freeIDs->back();
            comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, NEW_CLIENT_PORT);
            qDebug() << "0: Abonent creation request. Assigned ID: " << freeIDs->back();
            takenIDs->push_back(std::make_pair(freeIDs->back(),0));
            freeIDs->pop_back();
            currentAbonents++;
        break;}

        case 1:{ // One means that abonent asks if the limit is reached
            quint16 requestee;
            rReqSs >> requestee;
            resSs << "1 ";
            if (currentConnections < maximumConnections) {
                resSs << "0";
                updateValue(*takenIDs, requestee, 1);
            }
            else{
                resSs << "1";
                updateValue(*takenIDs, requestee, 2);
            }
            comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, requestee);
            qDebug() << "1: ATS Limit check request: " << resSs.str();
        break;}

        case 2:{ // Two means abonent is "ready" and is trying to call someone
            quint16 requestee, addressee;
            rReqSs >> requestee;
            if (rReqSs >> addressee && !rReqSs.fail()) {
               updateValue(*takenIDs, requestee, 3);
                resSs << "3 "; // Three means this abonent is BEING CALLED BY someone
                resSs << requestee;
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, addressee);
                qDebug() << "2: An attempt to call from " << requestee << " to " << addressee;
            }
            else {
                comm->sendToAddress(QString::fromStdString("Error while parsing data!"), NETWORK_IP, requestee);
            }

        break;}

        case 3:{ // Answer from the called. If positive, establish connection
            quint16 respondant, caller;
            bool respond;
            rReqSs >> respondant;
            rReqSs >> caller;
            rReqSs >> respond;
            if (respond){
                updateValue(*takenIDs, respondant, 4);
                updateValue(*takenIDs, caller, 4);
                connections.push_back(std::make_pair(caller,respondant));
                resSs << "4"; // Four means connection is now established and the two are in a call
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, caller);
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, respondant);
                currentConnections++;
            }
            else{
                updateValue(*takenIDs, respondant, 0);
                resSs << "2"; // Call was rejected
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, caller);
            }
        break;}

        case 5:{ // Five is reserved for message transmission between two clients
            quint16 sender;
            rReqSs >> sender;
            std::string str = rReqSs.str();
            qDebug() << str;
            std::regex regex_pattern(R"((?:\d+\s+){2})");
            std::string result = std::regex_replace(str, regex_pattern, "");
            resSs << "5 " << sender << " " << result;
            qDebug() << result;
            qDebug() << resSs.str();
            int index = indexFind(connections, sender);
            qDebug() << index << " " << connections[index];
            if (sender == connections[index].first){
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].second);
            }
            else{
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].first);
            }
        break;}

        case 6:{ // Six is reserved for losing connection
            quint16 sender;
            rReqSs >> sender;
            int index = indexFind(connections, sender);
            resSs << "6"; // Connection is lost

            comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, sender);
            updateValue(*takenIDs, sender, 0);
            if (sender == connections[index].first){
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].second);
                updateValue(*takenIDs, connections[index].second, 0);
            }
            else{
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].first);
                updateValue(*takenIDs, connections[index].first, 0);
            }
            connections.erase(connections.begin() + index);
            currentConnections--;
        break;}

        case 7:{ // Seven is reserved for abonent deletion and their number recovery when client is closed
            quint16 abonent;
            rReqSs >> abonent;
            int count = 0;
            for (std::pair<quint16, int> pair : *takenIDs) {
                if (pair.first!=abonent) count++;
                if (pair.first==abonent) break;
            }
            takenIDs->erase(takenIDs->begin()+count);
            freeIDs->push_back(abonent);
            currentAbonents--;
        break;}
    }
    emit messageNotice(*takenIDs, connections); // We notify the interface that something was recieved to update view

}
/////////////////////////////////////OUTSIDE OF CLASS FUNCTIONS///////////////////////////////////
int indexFind(QVector<std::pair<quint16, quint16>> v, int key){
    for (qsizetype i = 0; i < v.size(); i++){
        if (v[i].first == key || v[i].second == key){
            return i;
        }
    }
    return -1;
}
void updateValue(QVector<std::pair<quint16, int>> &takenIDs, quint16 searchKey, int newValue) {
    for (auto& item : takenIDs) {
        if (item.first == searchKey) {
            item.second = newValue;
        }
    }
}
