#ifndef HANDLERFACTORY_H
#define HANDLERFACTORY_H

#include <QObject>
#include <QThread>
#include <QPointer>
#include "clienthandler.h"

class HandlerFactory : public QObject
{
    Q_OBJECT
public:
    enum HandlerType{
        Asynchronous,
        Synchronous
    };

    explicit HandlerFactory(QObject *parent, HandlerType handlerType);

    void create(qintptr socketDescriptor);
    ~HandlerFactory();
signals:
    void reSended(QByteArray data,qintptr whoto);

public slots:
    void reSend(QByteArray data,qintptr whoto);

private:
    void sendList(ClientHandler *clienthandler);
    QObject * _parent;
    HandlerType _handlerType;
    QList<QPointer<ClientHandler>> clientHandlers;
};

#endif // HANDLERFACTORY_H
