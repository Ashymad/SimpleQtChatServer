#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
    handlerFactory = new HandlerFactory(this, HandlerFactory::Asynchronous);
}

MyServer::~MyServer()
{
    handlerFactory->deleteLater();
}

void MyServer::startServer(const QHostAddress & address, quint16 port)
{
    if(!this->listen(address,port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening on port" << serverPort();
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    handlerFactory->create(socketDescriptor);
}
