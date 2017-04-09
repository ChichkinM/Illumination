#ifndef MAINOBJ_H
#define MAINOBJ_H

#include <QObject>
#include <QColor>
#include "networkclient.h"

#define CMD_TO_LED 0xA0

#define CMD_MODE_COLOR 0xC0
#define CMD_MODE_FLUCT 0xC1
#define CMD_MODE_MUSIC 0xC2

class MainObj : public QObject
{
    Q_OBJECT
public:
    explicit MainObj(QObject *parent = 0);

    void writeCmd(int mode);

    void networkConnect();

    void setColorR(int value) { color->setRed(value); }
    void setColorG(int value) { color->setGreen(value); }
    void setColorB(int value) { color->setBlue(value); }
    void setDelayLED(int value) { delayLED = value; }

private:
    NetworkClient *client;

    QColor *color;
    int delayLED;

signals:
    void networkStateChange(int);

public slots:
};

#endif // MAINOBJ_H
