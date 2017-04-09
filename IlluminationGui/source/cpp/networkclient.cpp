#include "networkclient.h"
#include <QThread>

#define RECONNECTION_INTERVAL 500
#define RECONNECTION_MAX_TRY 8

NetworkClient::NetworkClient(QObject *parent) : QObject(parent)
{
    client = new QTcpSocket();
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(connect()));

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

    int state = client->state();
    emit connectionStateChange(state);

    if(state == QAbstractSocket::UnconnectedState || state == QAbstractSocket::ConnectedState)
        timer->stop();
}

void NetworkClient::write(QByteArray data)
{
    client->write(data);
    qDebug() << "write data";
}
