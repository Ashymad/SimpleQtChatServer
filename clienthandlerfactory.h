#ifndef CLIENTHANDLERFACTORY_H
#define CLIENTHANDLERFACTORY_H

#include <QObject>

class ClientHandlerFactory : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandlerFactory(QObject *parent = 0);
    ~ClientHandlerFactory();

signals:

public slots:
};

#endif // CLIENTHANDLERFACTORY_H
