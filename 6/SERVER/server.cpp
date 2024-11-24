#include "server.h"

Server::Server(int argc, char *argv[]) : QCoreApplication(argc, argv){
    comm = new Communicator(QHostAddress("127.0.0.1"), 1984);
    connect(comm, &Communicator::messageRecieved, this, &Server::handleMessage);
    this->poly_complex=new Polynom<TComplex>(3);
    this->poly_double=new Polynom<double>(3);
    std::stringstream fp;
    fp << "1+0i 2+0i 3+0i 4+0i";
    fp >> *poly_complex;
    fp << "4 5 6 7";
    fp >> *poly_double;
    qDebug() << "start";
}
Server::~Server(){
    delete poly_complex;
    delete poly_double;
}
void Server::handleMessage(QString &message){
    QHostAddress addressee = QHostAddress("127.0.0.1");
    quint16 addresseePort = 1985;
    std::stringstream rReqSs, resSs; // recieved request stringstream
    qDebug() << "reading";
    rReqSs << message.toStdString();
    bool use_complex_polynom;
    rReqSs >> use_complex_polynom;
    int menu_number;
    rReqSs >> menu_number;
    qDebug() << "Recieved:";
    switch (menu_number) {
    case 1:{
    int new_poly_size;
    qDebug() << "1:New polynomial creation request.";
    if (rReqSs >> new_poly_size || !rReqSs.fail()){
        qDebug() << "Size:" << new_poly_size;
        if (new_poly_size <= 0) {
            comm->sendToAddress("0", addressee, addresseePort); //if it's a zero polynomial
            return;
        }
        std::stringstream check;
        std::string current_root;
        int root_counter = 0;
        check.str(rReqSs.str());     // <==== a copy of rReqSs to check roots. BUT!
        std::string *dummy = new std::string; // rReqSs has a menu number and a number of roots
        check >> *dummy;           // in first two iterations. So we extract the first
        check >> *dummy;          // two in dummy and get rid of it.
        delete dummy;            // This way, we get an ss of roots ONLY. Profit!
        while (!check.eof()){
            if (check >> current_root || !check.fail()){
                root_counter++;
                if (is_complex_from_string(current_root) && !use_complex_polynom){
                    comm->sendToAddress("Requested polynomial of type double, but a complex root has been provided. Operation aborted.", addressee, addresseePort);
                    qDebug() << "Requested: operation with <double>. Recieved: <TComplex>"
                             << message;
                    return;
                }
            }
            else{
                comm->sendToAddress("Error while parsing data from request!", addressee, addresseePort);
                qDebug() << "Error while parsing data from request! Data:"
                         << message;
                return;
            }
        }
        if (root_counter - 1 < new_poly_size) {
            comm->sendToAddress("Expected more roots than provided", addressee, addresseePort);
            qDebug() << "Not enough roots to create a polynomial. Data:"
                     << message;
            return;
            /*we HAVE TO do this separately or else it
            goes copying the only root to all indexes which is nuts*/
        }

        if(use_complex_polynom){
            this->poly_complex = new Polynom<TComplex>(new_poly_size);
            rReqSs >> *poly_complex; // and finally we can create a polynomial
            resSs << "The created polynomial: " << *poly_complex;
        }
        else{
            this->poly_double = new Polynom<double>(new_poly_size);
            rReqSs >> *poly_double; // and finally we can create a polynomial
            resSs << "The created polynomial: " << *poly_double;
        }

        comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
        qDebug() << "Polynomial has been successfully sent.";
        qDebug() << "Sent polynomial:" << resSs.str();
        return;
    }
    else {
        comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
        qDebug() << "Error while parsing data from request! Data:"
                 << message;
        return;
    }
    break;
}
    case 2:
    {
        qDebug() << "2:Polynomial resize request.";
        int new_roots_size = 0;
        if(use_complex_polynom){
            if(rReqSs >> new_roots_size || !rReqSs.fail()){
                poly_complex->resize(new_roots_size);
                comm->sendToAddress("The array of roots has been successfully resized", addressee, addresseePort);
                qDebug() << "The array of roots has been successfully resized";
                return;
            }
            else{
                comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                qDebug() << "Error while parsing data from request! Data:"
                         << message;
                return;
            }
            break;
        }
        else {
            if(rReqSs >> new_roots_size || !rReqSs.fail()){
                poly_double->resize(new_roots_size);
                comm->sendToAddress("The array of roots has been successfully resized", addressee, addresseePort);
                qDebug() << "The array of roots has been successfully resized";
                return;
            }
            else{
                comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                qDebug() << "Error while parsing data from request! Data:"
                         << message;
                return;
            }
            break;
        }
    }
    case 3:
    {
        qDebug() << "3:Request to calculate the value in x.";
        std::string current_x;
        double x_double;
        TComplex x_complex;
        rReqSs >> current_x;
        if (is_complex_from_string(current_x) && !use_complex_polynom){
            comm->sendToAddress("Requested polynomial of type double, but a complex x has been provided. Operation aborted.", addressee, addresseePort);
            return;
        }
        else if (is_complex_from_string(current_x) && use_complex_polynom){
            rReqSs << current_x;
            rReqSs >> x_complex;
            if(rReqSs >> x_complex || !rReqSs.fail()){
                resSs << poly_complex->solve_for_x(x_complex);
                comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "Result in x has been successfully sent.";
                qDebug() << "Sent result:" << resSs.str();
                return;
            }
            else{
                comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                qDebug() << "Error while parsing data from request! Data:"
                         << message;
                return;
            }
        }
        else {
            rReqSs >> x_double;
            if(rReqSs >> x_double || !rReqSs.fail()){
                resSs << poly_double->solve_for_x(x_double);
                comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "Result in x has been successfully sent.";
                qDebug() << "Sent result:" << resSs.str();
                return;
            }
            else{
                comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                qDebug() << "Error while parsing data from request! Data:"
                         << message;
                return;
            }
        }
        break;
    }
    case 4:
    {
        qDebug() << "4:Request to change the value of A_n.";
        std::string current_a_n;
        double new_a_n_double;
        TComplex new_a_n_complex;
        rReqSs >> current_a_n;
        if (is_complex_from_string(current_a_n) && !use_complex_polynom){
            comm->sendToAddress("Requested polynomial of type double, but a complex a_n has been provided. Operation aborted.", addressee, addresseePort);
            return;
        }
        else if (is_complex_from_string(current_a_n) && use_complex_polynom){
            rReqSs << current_a_n;
            rReqSs >> new_a_n_complex;
            if(rReqSs >> new_a_n_complex || !rReqSs.fail()){
                poly_complex->set_a_n(new_a_n_complex);
                resSs << new_a_n_complex;
                comm->sendToAddress("Coefficient A_n has been changed to: " + QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "Coefficient A_n has been successfully changed.";
                return;
            }
            else{
                comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                qDebug() << "Error while parsing data from request! Data:"
                         << message;
                return;
            }
        }
        else {
            rReqSs << current_a_n;
            rReqSs >> new_a_n_double;
            if(rReqSs >> new_a_n_double || !rReqSs.fail()){
                poly_double->set_a_n(new_a_n_double);
                resSs << new_a_n_double;
                comm->sendToAddress("Coefficient A_n has been changed to: " + QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "Coefficient A_n has been successfully changed.";
                return;
            }
            else{
                comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                qDebug() << "Error while parsing data from request! Data:"
                         << message;
                return;
            }
        }
        break;
    }
    case 5:
    {
        qDebug() << "5:Request to change a certain root.";
        int index;
        std::string current_root;
        double new_root_double;
        TComplex new_root_complex;
        rReqSs >> current_root;
        if (is_complex_from_string(current_root) && !use_complex_polynom){
            comm->sendToAddress("Requested polynomial of type double, but a complex root has been provided. Operation aborted.", addressee, addresseePort);
            return;
        }
        else if (is_complex_from_string(current_root) && use_complex_polynom) {
            if(rReqSs >> index || !rReqSs.fail()) {
                if(rReqSs >> new_root_complex || !rReqSs.fail()){
                    poly_complex->change_root(index,new_root_complex);
                    comm->sendToAddress("Root has been changed succesfully!", addressee, addresseePort);
                    qDebug() << "Root has been changed succesfully.";
                    return;
                }
                else{
                    comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                    qDebug() << "Error while parsing data from request! Data:"
                             << message;
                    return;
                }
            }
            else {
                comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                qDebug() << "Error while parsing data from request! Data:"
                         << message;
                return;
            }
        }
        else {
            if(rReqSs >> index || !rReqSs.fail()) {
                if(rReqSs >> new_root_double || !rReqSs.fail()){
                    poly_double->change_root(index,new_root_double);
                    comm->sendToAddress("Root has been changed succesfully!", addressee, addresseePort);
                    qDebug() << "Root has been changed succesfully.";
                    return;
                }
                else{
                    comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                    qDebug() << "Error while parsing data from request! Data:"
                             << message;
                    return;
                }
            }
            else {
                comm->sendToAddress("Error while parsing data!", addressee, addresseePort);
                qDebug() << "Error while parsing data from request! Data:"
                         << message;
                return;
            }
        }

        break;
    }
    case 6:{
        int index; // I want at least some clarity. Let this store the missing index if there is one due to resize.
        qDebug() << "6:Request to display the polynomial in unexpanded form.";
        if (use_complex_polynom) {
            index = poly_complex->are_roots_full();
            if (index == -1){
                poly_complex->set_display_format(0);
                resSs << *poly_complex;
                comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "Polynomial has been sent succesfully. Sent:" << QString::fromStdString(resSs.str());
                return;
            }
            else{
                resSs<<index;
                comm->sendToAddress("One or more indexes is empty. First met empty index: " + QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "One or more indexes is empty. Operation aborted.";
            }
        }
        else {
            index = poly_double->are_roots_full();
            if (index == -1){
                poly_double->set_display_format(0);
                resSs << *poly_double;
                comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "Polynomial has been sent succesfully. Sent:" << QString::fromStdString(resSs.str());
                return;
            }
            else{
                resSs<<index;
                comm->sendToAddress("One or more indexes is empty. First met empty index: " + QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "One or more indexes is empty. Operation aborted.";
            }
        }
        break;
    }
    case 7:
        int index;
        qDebug() << "6:Request to display the polynomial in expanded form.";
        if (use_complex_polynom) {
            index = poly_complex->are_roots_full();
            if (index == -1){
                poly_complex->set_display_format(1);
                resSs << *poly_complex;
                comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "Polynomial has been sent succesfully. Sent:" << QString::fromStdString(resSs.str());
                return;
            }
            else{
                resSs<<index;
                comm->sendToAddress("One or more indexes is empty. First met empty index: " + QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "One or more indexes is empty. Operation aborted.";
            }
        }
        else {
            index = poly_double->are_roots_full();
            if (index == -1){
                poly_double->set_display_format(1);
                resSs << *poly_double;
                comm->sendToAddress(QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "Polynomial has been sent succesfully. Sent:" << QString::fromStdString(resSs.str());
                return;
            }
            else{
                resSs<<index;
                comm->sendToAddress("One or more indexes is empty. First met empty index: " + QString::fromStdString(resSs.str()), addressee, addresseePort);
                qDebug() << "One or more indexes is empty. Operation aborted.";
            }
        }
        break;
    }
}
