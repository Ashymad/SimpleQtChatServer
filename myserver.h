#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include "handlerfactory.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject* parent = 0);
    void startServer(const QHostAddress & address = QHostAddress::Any, quint16 port = 1234);
    ~MyServer();
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    HandlerFactory * handlerFactory;
};

#endif // MYSERVER_H

