#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QDebug>
#include <QTime>

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandler(qintptr iID, QObject* parent = 0);

    enum sendIdentifier
    {
        message = 1,
        joined = 2,
        left = 3,
        list = 4
    };
    static const qintptr All = 0;

    static QByteArray prepareData(sendIdentifier sID, const QVector<QString> &data);
    QString getName() const;
    qintptr getDescriptor() const;
signals:
    void error(QTcpSocket::SocketError socketerror);
    void reSend(QByteArray data, qintptr whoto = All);

public slots:
    void run();
    void readyRead();
    void reSended(QByteArray data, qintptr whoto);
    void disconnected();

private:
    QString _name;
    QTcpSocket* socket;
    int socketDescriptor;

};

#endif // MYTHREAD_H

