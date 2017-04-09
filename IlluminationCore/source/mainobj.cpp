#include "mainobj.h"
#include <QDebug>

#define CMD_TO_LED 0xA0
#define CMD_FROM_LED 0xA1

#define CMD_MODE_COLOR 0xC0
#define CMD_MODE_FLUCT 0xC1
#define CMD_MODE_MUSIC 0xC2

#define CMD_GET_STATUS 0xBC

#define WAIT_RESPONSE 200

MainObj::MainObj(QObject *parent) : QObject(parent)
{    
    qRegisterMetaType<QList<QString>>("ListComPorts");

    serialIsOpen = false;
    response = false;

    timerForWaiter = new QTimer();
    waiter = new QEventLoop();
    timer = new QTimer();

    timer->setInterval(500);
    timerForWaiter->setInterval(WAIT_RESPONSE);
    timerForWaiter->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(getLedStatus()));
    connect(timerForWaiter, SIGNAL(timeout()), this, SLOT(noResponse()));

    //TODO можно сделать одну функцияю для приема и передачи команд, но как-то защитить ее
    SerialPort *serial = new SerialPort();
    NetworkServer *server = new NetworkServer();
    BassHandler *bass = new BassHandler();

    serialThread = new QThread();
    networkThread = new QThread();
    bassThread = new QThread();

    serial->moveToThread(serialThread);
    server->moveToThread(networkThread);
    bass->moveToThread(bassThread);

    connect(serial, SIGNAL(newData(QByteArray)), this, SLOT(parseResponce(QByteArray)));
    connect(this, SIGNAL(serialOpen(QString)), serial, SLOT(open(QString)));
    connect(this, SIGNAL(serialClose()), serial, SLOT(close()));
    connect(this, SIGNAL(serialWrite(QByteArray)), serial, SLOT(write(QByteArray)));
    connect(this, SIGNAL(serialGetPots()), serial, SLOT(getAvailablePorts()));
    connect(serial, SIGNAL(availablePorts(ListComPorts)), this, SLOT(setAvailablePorts(ListComPorts)));
    connect(serial, SIGNAL(stateChanged(bool)), this, SLOT(setSerialState(bool)));

    connect(server, SIGNAL(newData(QByteArray)), this, SLOT(sendCmd(QByteArray)));
    connect(this, SIGNAL(networkOpen()), server, SLOT(open()));
    connect(this, SIGNAL(networkClose()), server, SLOT(close()));

    connect(bass, SIGNAL(updateColor(QByteArray)), this, SLOT(sendCmd(QByteArray)));
    connect(this, SIGNAL(bassInit()), bass, SLOT(init()));
    connect(this, SIGNAL(bassStart()), bass, SLOT(start()));
    connect(this, SIGNAL(bassStop()), bass, SLOT(stop()));

    serialThread->start();
    networkThread->start();

    //    bassThread->start();
    //    emit bassInit();
    //    emit bassStart();
}

void MainObj::openSerialPort(QString comName)
{    
    if(comName != COM_NAME_UNKNOWN)
    {
        this->comName = comName;
        emit serialOpen(comName);
    }
    else
    {
        getAvailablePorts();
        qDebug() << availablePorts.count();

        foreach (QString port, availablePorts)
        {
            serialOpenWithConfirm(port);

            if(serialIsOpen)
                getLedStatus(true);

            if(!response)
                serialCloseWithConfirm();
            else
            {
                this->comName = port;
                break;
            }
        }

        qDebug() << "end searching result" << this->comName << serialIsOpen;
    }

    //    timer->start();
}

void MainObj::parseResponce(QByteArray cmd)
{
    qDebug() << "responce" << cmd.toHex();
    response = true;

    if(waiter->isRunning())
        waiter->quit();
    if(timerForWaiter->isActive())
        timerForWaiter->stop();

}

//TODO при переключении с музыки на цвет может остаться цвет с музыки
void MainObj::sendCmd(QByteArray cmd)
{
    qDebug() << "send cmd";

    if(cmd[0] == (char)CMD_TO_LED)
    {
        switch((int)cmd[1])
        {
        case (int)CMD_MODE_COLOR:
        case (int)CMD_MODE_FLUCT:

            //            if(h->isRun())
            //                h->stop();

            emit serialWrite(cmd);
            break;

        case (int)CMD_MODE_MUSIC:
            emit bassStart();
            break;
        }
    }

    if(cmd[0] == (char)BASS_NEW_COLOR)
    {
        cmd.prepend(CMD_TO_LED);
        cmd[1] = CMD_MODE_COLOR;
        cmd.append((char)0);
    }

    emit serialWrite(cmd);
}

void MainObj::getLedStatus(bool waitResponse)
{
    QByteArray cmd;
    cmd.append(0xA0);
    cmd.append(0xBC);

    qDebug() << "status";

    emit serialWrite(cmd);

    if(waitResponse)
    {
        timerForWaiter->start();
        waiter->exec();
    }
}

//TODO убрать много маленьких функций
void MainObj::getAvailablePorts()
{
    emit serialGetPots();
    waiter->exec();
}

void MainObj::serialOpenWithConfirm(QString port)
{
    emit serialOpen(port);
    waiter->exec();
}

void MainObj::serialCloseWithConfirm()
{
    emit serialClose();
    waiter->exec();
}

void MainObj::setAvailablePorts(QList<QString> ports)
{
    availablePorts = ports;
    if(waiter->isRunning())
        waiter->quit();
}

void MainObj::setSerialState(bool state)
{
    serialIsOpen = state;
     if(waiter->isRunning())
         waiter->quit();
}

void MainObj::noResponse()
{
    response = false;
     if(waiter->isRunning())
         waiter->quit();
}
