#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class NetworkServer : public QObject
{
    Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = 0);

    ~NetworkServer();
private:
    QList<QTcpSocket*> *clients;
    QTcpServer *server;

signals:
    void newData(QByteArray data);

public slots:
    void open();
    void close();
    void write(QByteArray cmd);

private slots:
    void connectionHandler();
    void read();
    void disconnectionHandler();
};

#endif // NETWORKSERVER_H
