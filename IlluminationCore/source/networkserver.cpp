#include "networkserver.h"
#include <QDebug>

#define SERVER_PORT_DEF 333

NetworkServer::NetworkServer(QObject *parent) : QObject(parent)
{

}

NetworkServer::~NetworkServer()
{
    close();
}

void NetworkServer::open()
{
    clients = new QList<QTcpSocket*>();
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(connectionHandler()));

    qDebug() << "server start" << server->listen(QHostAddress::Any, SERVER_PORT_DEF);
}

void NetworkServer::close()
{
    for(int i = 0; i < clients->size(); i++)
    {
        if(clients->at(i)->isOpen())
            clients->at(i)->close();
        clients->removeAt(i);

        qDebug() << "disconnect client" << i;
    }

    if(server->isListening())
    {
        server->close();
        qDebug() << "server is open" << server->isListening();
    }
}

void NetworkServer::connectionHandler()
{
    QTcpSocket *client = server->nextPendingConnection();

    connect(client, SIGNAL(readyRead()), this, SLOT(read()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnectionHandler()));

    clients->append(client);

    qDebug() << "new connection";
}

void NetworkServer::disconnectionHandler()
{
    QTcpSocket *client = (QTcpSocket*)sender();

    for(int i = 0; i < clients->size(); i++)
        if(clients->at(i) == client)
        {
            if(clients->at(i)->isOpen())
                clients->at(i)->close();
            clients->removeAt(i);

            qDebug() << "disconnect client" << i;
        }
}

void NetworkServer::write(QByteArray cmd)
{
    for(int i = 0; i < clients->size(); i++)
        clients->at(i)->write(cmd);
}

void NetworkServer::read()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    emit newData(client->readAll());
}
