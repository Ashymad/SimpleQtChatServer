#include <QCoreApplication>
#include <iostream>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyServer server;
    quint16 port;
    std::cout << "Please specify port: ";
    std::cin >> port;
    std::cout << std::endl;
    server.startServer(QHostAddress::Any,port);

    return a.exec();
}
