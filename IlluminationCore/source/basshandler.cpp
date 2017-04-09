#include "basshandler.h"

#include "bass.h"
#include "basswasapi.h"

#include <QDebug>
#include <QtMath>


DWORD CALLBACK procHandler1(void *buffer, DWORD length, void *user)
{
    return TRUE;
}

BassHandler::BassHandler(QObject *parent) : QObject(parent)
{

}

void BassHandler::init()
{
    run = false;

    t = new QTimer();
    t->setInterval(50);
    connect(t, SIGNAL(timeout()), this, SLOT(update()));
}

void BassHandler::start()
{
    BASS_WASAPI_Free();
    BASS_Free();

    bool result;

//    BASS_WASAPI_DEVICEINFO info;
//    for(int i = 0; BASS_WASAPI_GetDeviceInfo(i, &info); i++)
//        qDebug() << i << info.mixfreq << info.name;

    if (HIWORD(BASS_GetVersion()) == BASSVERSION)
        printf("lib loaded\r\n");

    result = BASS_Init(0, 44100, BASS_DEVICE_DEFAULT, 0, NULL);
    qDebug() << "BASS_Init" << result;

    result = BASS_WASAPI_Init(17, 0, 0, BASS_WASAPI_BUFFER, 1, 0, &procHandler1, NULL);
    qDebug() << "BASS_WASAPI_Init" << result;

    result = BASS_WASAPI_Start();
    qDebug() << "BASS_WASAPI_Start" << result;

    t->start();

    run = true;
}

void BassHandler::stop()
{
    t->stop();

    BASS_WASAPI_Free();
    BASS_Free();

    run = false;
}

void BassHandler::update()
{
    float buf[1024];

    BASS_WASAPI_GetData(buf, BASS_DATA_FFT2048);

//    for(int i = 0; i < 1024; i++)
//        if(buf != 0)
//            qDebug() << i << buf[i];

    createColor(buf);
}

void BassHandler::createColor(float *buf)
{
    QByteArray result;
    result.append(BASS_NEW_COLOR);

    int spectrumVal, b0 = 0;

    for (int i = 0; i < 3; i++)
    {
        quint64 sum = 0;
        for (int x = 0; x < 15 / 3; x++)
        {
            float peak = 0;
            quint64 b1 = (quint64)qPow(2, x * i * 10 / (15 - 1));

            if (b1 > 1023)
                b1 = 1023;
            if (b1 <= b0)
                b1 = b0 + 1;

            for (; b0 < b1; b0++)
                if (peak < buf[1 + b0])
                    peak = buf[1 + b0];

            spectrumVal = (quint64)(qSqrt(peak) * 3 * 255 - 4);

            if (spectrumVal > 255)
                spectrumVal = 255;
            if (spectrumVal < 0)
                spectrumVal = 0;

            sum += spectrumVal;
        }
        result.append(sum / (15 / 3));
        //        lastChanges[indexes[i]]++;

    }

    emit updateColor(result);
}
