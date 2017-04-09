#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include "mainobj.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);



private:
    MainObj *mainObj;

signals:
    void networkStateChange(int stateNet);

public slots:
    void rbModeColor_clicked();
    void sbR_EditingFinished(int value);
    void sbG_EditingFinished(int value);
    void sbB_EditingFinished(int value);
    void sbDelay_EditingFinished(int value);
    void btnNetwork_clicked();

    int getNetworkState() { return 1;}

private slots:

};

#endif // MAINWINDOW_H
