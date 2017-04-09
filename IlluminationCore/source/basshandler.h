#ifndef BASS_HANDLER
#define BASS_HANDLER

#include <QObject>
#include <QTimer>
//#include "serialport.h"
#include <QMutex>

#define BASS_NEW_COLOR 0xBA

class BassHandler : public QObject
{
    Q_OBJECT
public:
    explicit BassHandler(QObject *parent = 0);

    isRun() { return run; }

public slots:
    void init();
    void start();
    void stop();

private:
    QTimer *t;
    void createColor(float *buf);
    bool run;

signals:
    void updateColor(QByteArray rgb);

private slots:
    void update();
};

#endif // TEST_H
