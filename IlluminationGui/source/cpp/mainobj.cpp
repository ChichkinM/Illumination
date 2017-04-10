#include "mainobj.h"

#include <QDebug>
#include <QSettings>
#include <QProcess>

MainObj::MainObj(QObject *parent) : QObject(parent)
{
    //    QSettings settings("HKEY_CURRENT_USER\\Control Panel\\Desktop", QSettings::NativeFormat);
    //    QString wallpaperPath = settings.value("WallPaper").toString();

    core = new QProcess();
    core->start("IlluminationCore.exe");

    client = new NetworkClient();
    connect(client, SIGNAL(stateConnected()), this, SIGNAL(networkStateConnected()));
    connect(client, SIGNAL(stateConnected()), this, SLOT(getSerialState()));
    connect(client, SIGNAL(stateConnecting()), this, SIGNAL(networkStateConnecting()));
    connect(client, SIGNAL(stateDisconnected()), this, SIGNAL(networkStateDisconnected()));
    connect(client, SIGNAL(stateDisconnected()), this, SIGNAL(ledStateDisconnected()));
    connect(client, SIGNAL(newData(QByteArray)), this, SLOT(parseData(QByteArray)));

    color = new QColor();
    delayLED = 0;
}

MainObj::~MainObj()
{
    core->close();
}

void MainObj::parseData(QByteArray data)
{
    if(data[0] == CMD_TO_GUI && data[1] == CMD_GET_STATUS)
        if((bool)data[2])
            emit ledStateConnected();
        else
            emit ledStateDisconnected();
}

void MainObj::getSerialState()
{
    QByteArray cmd;
    cmd.append(CMD_TO_CORE);
    cmd.append(CMD_GET_STATUS);

    client->write(cmd);
}

void MainObj::networkConnect()
{
    client->connect();
}

void MainObj::writeCmd(int mode)
{
    QByteArray cmd;

    switch (mode)
    {
    case (int)CMD_MODE_COLOR:
        cmd.append(0xA0);
        cmd.append(0xC0);
        cmd.append((char)color->red());
        cmd.append((char)color->green());
        cmd.append((char)color->blue());
        cmd.append((char)delayLED);

        client->write(cmd);
        break;
    }
}
