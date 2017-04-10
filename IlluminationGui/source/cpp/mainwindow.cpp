#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    mainObj = new MainObj();

    connect(mainObj, SIGNAL(networkStateConnected()), this, SIGNAL(networkStateConnected()));
    connect(mainObj, SIGNAL(networkStateConnecting()), this, SIGNAL(networkStateConnecting()));
    connect(mainObj, SIGNAL(networkStateDisconnected()), this, SIGNAL(networkStateDisconnected()));

    connect(mainObj, SIGNAL(ledStateConnected()), this, SIGNAL(ledStateConnected()));
    connect(mainObj, SIGNAL(ledStateDisconnected()), this, SIGNAL(ledStateDisconnected()));
}

MainWindow::~MainWindow()
{
    delete mainObj;
}

void MainWindow::btnRefresh_clicked()
{
    mainObj->networkConnect();
}

void MainWindow::rbModeColor_clicked()
{
    mainObj->writeCmd(CMD_MODE_COLOR);
}

void MainWindow::sbR_EditingFinished(int value)
{
    qDebug() << value;
    mainObj->setColorR(value);
    mainObj->writeCmd(CMD_MODE_COLOR);
}

void MainWindow::sbG_EditingFinished(int value)
{
    qDebug() << value;
    mainObj->setColorG(value);
    mainObj->writeCmd(CMD_MODE_COLOR);
}

void MainWindow::sbB_EditingFinished(int value)
{
    qDebug() << value;
    mainObj->setColorB(value);
    mainObj->writeCmd(CMD_MODE_COLOR);
}

void MainWindow::sbDelay_EditingFinished(int value)
{
    qDebug() << value;
    mainObj->setDelayLED(value);
}

void MainWindow::btnNetwork_clicked()
{
    mainObj->networkConnect();
}


