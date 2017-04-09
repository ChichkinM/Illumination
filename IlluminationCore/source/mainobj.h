#ifndef MAINOBJ_H
#define MAINOBJ_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QEventLoop>
#include "basshandler.h"
#include "serialport.h"
#include "networkserver.h"

#define COM_NAME_UNKNOWN "unknown"

class MainObj : public QObject
{
    Q_OBJECT
public:
    explicit MainObj(QObject *parent = 0);

    void openSerialPort(QString comName = COM_NAME_UNKNOWN);

private:
    QThread *serialThread;
    QThread *networkThread;
    QThread *bassThread;

    QTimer *timer;
    QEventLoop *waiter;
    QTimer *timerForWaiter;

    bool serialIsOpen;
    bool response;
    QString comName;

    QList<QString> availablePorts;

    void getAvailablePorts();

    void serialOpenWithConfirm(QString port);
    void serialCloseWithConfirm();

private slots:
    void sendCmd(QByteArray cmd);
    void parseResponce(QByteArray cmd);

    void getLedStatus(bool waitResponse = false);

    void setAvailablePorts(QList<QString> ports);
    void setSerialState(bool state);

    void noResponse();

signals:
    void serialOpen(QString portName);
    void serialClose();
    void serialWrite(QByteArray data);
    void serialGetPots();

    void networkOpen();
    void networkClose();

    void bassInit();
    void bassStop();
    void bassStart();
};

#endif // MAINOBJ_H
