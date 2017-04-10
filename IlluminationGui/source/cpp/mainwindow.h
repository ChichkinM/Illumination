#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include "mainobj.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);
    ~MainWindow();

private:
    MainObj *mainObj;

signals:
    networkStateConnected();
    networkStateConnecting();
    networkStateDisconnected();

    ledStateConnected();
    ledStateDisconnected();

public slots:
    void rbModeColor_clicked();
    void sbR_EditingFinished(int value);
    void sbG_EditingFinished(int value);
    void sbB_EditingFinished(int value);
    void sbDelay_EditingFinished(int value);
    void btnNetwork_clicked();

    int getNetworkState() { return 1;}

    void btnRefresh_clicked();
private slots:

};

#endif // MAINWINDOW_H
