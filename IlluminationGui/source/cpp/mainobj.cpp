#include "mainobj.h"

#include <QDebug>
#include <QSettings>

MainObj::MainObj(QObject *parent) : QObject(parent)
{
//    QSettings settings("HKEY_CURRENT_USER\\Control Panel\\Desktop", QSettings::NativeFormat);
//    QString wallpaperPath = settings.value("WallPaper").toString();

    
    client = new NetworkClient();
    connect(client, SIGNAL(connectionStateChange(int)), this, SIGNAL(networkStateChange(int)));

    color = new QColor();
    delayLED = 0;
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
