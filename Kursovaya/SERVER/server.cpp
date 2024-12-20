#include "server.h"

Server::Server(int k, int n) : QObject(){
    comm = new Communicator(QHostAddress("127.0.0.1"), 1984);
    connect(comm, &Communicator::messageRecieved, this, &Server::handleMessage);
    maximumAbonents = pow(2,n)-1;
    maximumConnections = pow(2,k);
    currentConnections = 0;
    currentAbonents = 0;
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

void Server::messageToAbonent(std::string message, quint16 sender) {
    std::stringstream resSs;
    resSs << "5 " << sender << " " << message;
    int index = indexFind(connections, sender);
    if (sender == connections[index].first){
        comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].second);
    }
    else{
        comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].first);
    }
}

void Server::connectAbonents(quint16 ab1, quint16 ab2) {
    std::stringstream resSs;
    updateValue(*takenIDs, ab1, 4);
    updateValue(*takenIDs, ab2, 4);
    connections.push_back(std::make_pair(ab1,ab2));
    resSs << "4"; // Four means connection is now established and the two are in a call
    comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, ab1);
    comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, ab2);
    currentConnections++;
}

void Server::disconnectAbonents(quint16 anyOfTheTwo) {
    std::stringstream resSs;
    int index = indexFind(connections, anyOfTheTwo);
    resSs << "6"; // Connection is lost
    comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, anyOfTheTwo);
    updateValue(*takenIDs, anyOfTheTwo, 0);
    if (anyOfTheTwo == connections[index].first){
        comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].second);
        updateValue(*takenIDs, connections[index].second, 0);
    }
    else{
        comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].first);
        updateValue(*takenIDs, connections[index].first, 0);
    }
    connections.erase(connections.begin() + index);
    currentConnections--;
}

void Server::ping(quint16 whoPinged) {
    std::stringstream resSs;
    resSs << "1 ";
    if (currentConnections < maximumConnections) {
        resSs << "0";
        updateValue(*takenIDs, whoPinged, 1);
    }
    else{
        resSs << "1";
        updateValue(*takenIDs, whoPinged, 2);
    }
    comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, whoPinged);
}
void Server::handleMessage(QString &message){
    std::stringstream rReqSs; // recieved request stringstream
    std::stringstream resSs; // response stringstream
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
            ping(requestee);
        break;}

        case 2:{ // Two means abonent is "ready" and is trying to call someone
            quint16 requestee, addressee;
            rReqSs >> requestee;
            if (rReqSs >> addressee && !rReqSs.fail()) {

                if (indexFind(*takenIDs,addressee) == -1){
                comm->sendToAddress(QString::fromStdString("7 Number not found!"), NETWORK_IP, requestee);
                    return;
                }
                if (takenIDs->at(indexFind(*takenIDs,addressee)).second == 3 || takenIDs->at(indexFind(*takenIDs,addressee)).second == 4 || takenIDs->at(indexFind(*takenIDs,addressee)).second == 1){
                    updateValue(*takenIDs, requestee, 0);
                    comm->sendToAddress(QString::fromStdString("7 Number is busy!"), NETWORK_IP, requestee);
                    return;
                }
                updateValue(*takenIDs, requestee, 3);
                updateValue(*takenIDs, addressee, 3);
                resSs << "3 "; // Three means this abonent is BEING CALLED BY someone
                resSs << requestee;
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, addressee);
                qDebug() << "2: An attempt to call from " << requestee << " to " << addressee;
            }
            else {
                comm->sendToAddress(QString::fromStdString("7 Error while parsing data!"), NETWORK_IP, requestee);
            }

        break;}

        case 3:{ // Answer from the called or abortion. If positive, establish connection
            quint16 respondant, caller;
            bool respond;
            rReqSs >> respondant;
            rReqSs >> caller;
            rReqSs >> respond;
            if (respond){
                connectAbonents(respondant, caller);
            }
            else{
                updateValue(*takenIDs, respondant, 0);
                updateValue(*takenIDs, caller, 0);
                resSs << "2"; // Call was rejected
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, caller);
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, respondant);
            }
        break;}

        case 5:{ // Five is reserved for message transmission between two clients
            quint16 sender;
            rReqSs >> sender;
            std::string str = rReqSs.str();
            std::regex regex_pattern(R"((?:\d+\s+){2})");
            std::string result = std::regex_replace(str, regex_pattern, "");
            messageToAbonent(result, sender);
        break;}

        case 6:{ // Six is reserved for losing connection
            quint16 sender;
            rReqSs >> sender;
            disconnectAbonents(sender);
        break;}

        case 7:{ // Seven is reserved for abonent deletion and their number recovery when client is closed
            quint16 abonent;
            rReqSs >> abonent;
            int index = indexFind(connections, abonent);
            if (index != -1) {
                connections.erase(connections.begin() + index); // If abonent was in a call
                currentConnections--;
            }
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
    emit messageNotice(*takenIDs, connections, maximumAbonents, maximumConnections); // We notify the interface that something was recieved to update view

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
int indexFind(QVector<std::pair<quint16, int> > v, int key) {
    for (qsizetype i = 0; i < v.size(); i++){
        if (v[i].first == key){
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

