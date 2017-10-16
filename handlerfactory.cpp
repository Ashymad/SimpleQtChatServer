#include "handlerfactory.h"

HandlerFactory::HandlerFactory(QObject *parent, HandlerType handlerType) :
    QObject(parent),
    _handlerType(handlerType)
{
    _parent = parent;
    qRegisterMetaType<qintptr>("qintptr");
}

void HandlerFactory::create(qintptr socketDescriptor)
{
    QPointer<ClientHandler> clienthandler = new ClientHandler(socketDescriptor);

    //this - handler connections
    connect(clienthandler,SIGNAL(reSend(QByteArray,qintptr)),
            this,SLOT(reSend(QByteArray,qintptr)));
    connect(this,SIGNAL(reSended(QByteArray,qintptr)),
            clienthandler,SLOT(reSended(QByteArray,qintptr)));

    if (_handlerType == Synchronous)
    {
        QThread * thread = new QThread;

        //thread - handler connections
        connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
        connect(thread,SIGNAL(started()),clienthandler,SLOT(run()));
        connect(clienthandler,SIGNAL(destroyed()),thread,SLOT(quit()));

        clienthandler->moveToThread(thread);
        thread->start();
    }
    else
    {
        clienthandler->run();
    }

    sendList(clienthandler);
    clientHandlers.append(clienthandler);
}

void HandlerFactory::reSend(QByteArray data,qintptr whoto)
{
    emit reSended(data,whoto);
}

void HandlerFactory::sendList(ClientHandler * clienthandler)
{
    QVector<QString> data;
    for(const QPointer<ClientHandler> & QpCH : clientHandlers)
    {
        if(QpCH == nullptr)
        {
            clientHandlers.removeOne(QpCH);
        }
        else
        {
            data.push_back(QpCH->getName());
        }
    }
    if(clientHandlers.isEmpty()){return;}
    qDebug() << clienthandler->getDescriptor() << " Sending list, size:" << data.size();
    emit reSended(ClientHandler::prepareData(ClientHandler::list,data),
                  clienthandler->getDescriptor());
}

HandlerFactory::~HandlerFactory()
{

}

