#include "networkclient.h"
#include <QThread>

#define RECONNECTION_INTERVAL 500
#define RECONNECTION_MAX_TRY 8

NetworkClient::NetworkClient(QObject *parent) : QObject(parent)
{
    client = new QTcpSocket();
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(connect()));
    QObject::connect(client, SIGNAL(readyRead()), this, SLOT(read()));

    timer = new QTimer();
    timer->setInterval(RECONNECTION_INTERVAL);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(reconnection()));
}

void NetworkClient::connect()
{
    reconnectionCount = 0;
    timer->start();
}

void NetworkClient::reconnection()
{
    if(reconnectionCount++ < RECONNECTION_MAX_TRY)
        client->connectToHost("127.0.0.1", 333);

    switch((int)client->state())
    {
    case QAbstractSocket::ConnectedState:
        emit stateConnected();
        timer->stop();
        break;
    case QAbstractSocket::ConnectingState:
        emit stateConnecting();
        break;
    case QAbstractSocket::UnconnectedState:
        emit stateDisconnected();
        timer->stop();
        break;
    }
}

void NetworkClient::write(QByteArray data)
{
    client->write(data);
    qDebug() << "write data";
}

void NetworkClient::read()
{
    emit newData(client->readAll());
}
