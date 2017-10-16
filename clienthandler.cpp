#include "clienthandler.h"

ClientHandler::ClientHandler(qintptr ID ,QObject *parent) :
    QObject(parent)
{
    socketDescriptor = ID;
}

void ClientHandler::run()
{
    qDebug() << socketDescriptor << " Starting handler";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << socketDescriptor << " Client connected";

}

void ClientHandler::readyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_4);
    qint16 identifier;
    QString data;
    in >> identifier;
    in >> data;
    QVector<QString> vecData;
    vecData.push_back(data);
    switch(identifier)
    {
    case 1: //Client::message
        qDebug() <<  socketDescriptor << " Message sent:" << data;
        vecData.push_back(_name);
        emit reSend(prepareData(ClientHandler::message, vecData));
        break;
    case 2: //Client::name
        qDebug() <<  socketDescriptor << " Client identified itself as" << data;
        emit reSend(prepareData(ClientHandler::joined, vecData));
        _name = data;
        break;
    default:
        qDebug() << socketDescriptor <<
                    " Error: client send data with an unkown identifier (" << identifier << ")";
        socket->readAll();
    }
}


QByteArray ClientHandler::prepareData(sendIdentifier sID, const QVector<QString> & data){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);
    out << (quint16)sID;
    out << data;
    out << QTime::currentTime();
    return block;
}

QString ClientHandler::getName() const
{
    return _name;
}

qintptr ClientHandler::getDescriptor() const
{
    return socketDescriptor;
}

void ClientHandler::reSended(QByteArray data,qintptr whoto)
{
    if(whoto == All || whoto == socketDescriptor)
    {
        socket->write(data);
    }
}

void ClientHandler::disconnected()
{
    QVector<QString> vecName;
    vecName.push_back(_name);
    emit reSend(prepareData(ClientHandler::left, vecName));
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    this->deleteLater();
}
