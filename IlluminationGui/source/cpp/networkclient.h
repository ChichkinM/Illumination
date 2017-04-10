#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QTimer>
#include <QtNetwork/QTcpSocket>

class NetworkClient : public QObject
{
    Q_OBJECT
public:
    explicit NetworkClient(QObject *parent = 0);

    void write(QByteArray data);

private:
    QTcpSocket *client;
    QTimer *timer;

    int reconnectionCount;

public slots:
    void connect();

signals:
    void stateConnected();
    void stateDisconnected();
    void stateConnecting();

    void newData(QByteArray data);

private slots:
    void reconnection();
    void read();
};

#endif // NETWORKCLIENT_H
