#include "server.h"

Server::Server(int k, int n) : QObject(){
    comm = new Communicator(QHostAddress("127.0.0.1"), 1984);
    connect(comm, &Communicator::messageRecieved, this, &Server::handleMessage);
    maximumConnections = pow(2,k);
    currentConnections = 0;
    freeIDs = new std::vector<quint16>;
    for (quint16 i = 10000; i < pow(2,n)-1; i++){
        freeIDs->push_back(i);
    }
    qDebug() << "Start";
}
Server::~Server(){
    delete comm;
    delete freeIDs;
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

        case 0: // Zero means a creation request, and it will assign an ID
            resSs << "0 ";
            resSs << freeIDs->back();
            comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, NEW_CLIENT_PORT);
            qDebug() << "0: Abonent creation request. Assigned ID:" << freeIDs->back();
            freeIDs->pop_back();
            return;
        break;

        case 1:{ // One means that abonent asks if the limit is reached
            quint16 requestee;
            rReqSs >> requestee;
            resSs << "1 ";
            currentConnections <= maximumConnections ? resSs << "0" : resSs << "1";
            comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, requestee);
            qDebug() << "1: ATS Limit check request: " << resSs.str();
            return;
        break;}

        case 2:{ // Two means abonent is "ready" and is trying to call someone
            quint16 requestee, addressee;
            rReqSs >> requestee;
            rReqSs >> addressee;
            resSs << "3 "; // Three means this abonent is BEING CALLED BY someone
            resSs << requestee;
            comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, addressee);
            qDebug() << "2: An attempt to call from " << requestee << " to " << addressee;
            return;
        break;}

        case 3:{ // Answer from the called. If positive, establish connection
            quint16 respondant, caller;
            bool respond;
            rReqSs >> respondant;
            rReqSs >> caller;
            rReqSs >> respond;
            if (respond){
                connections.push_back(std::make_pair(caller,respondant));
                resSs << "4"; // Four means connection is now established and the two are in a call
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, caller);
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, respondant);
                currentConnections++;
            }
            else{
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
            if (sender == connections[index].first){
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].second);

            }
            else{
                comm->sendToAddress(QString::fromStdString(resSs.str()), NETWORK_IP, connections[index].first);
            }
            connections.erase(connections.begin() + index);
            currentConnections--;
            return;
        break;}
    }
}
/////////////////////////////////////OUTSIDE OF CLASS FUNCTIONS///////////////////////////////////
int indexFind(std::vector<std::pair<quint16, quint16>> v, int key){
    for (size_t i = 0; i < v.size(); i++){
        if (v[i].first == key || v[i].second == key){
            return i;
        }
    }
    return -1;
}
