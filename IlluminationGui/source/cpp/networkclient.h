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
    void connectionStateChange(int state);

private slots:
    void reconnection();
};

#endif // NETWORKCLIENT_H
