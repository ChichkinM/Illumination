#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QMutex>
#include <QtSerialPort/QSerialPort>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);
    ~SerialPort();

public slots:
    void open(QString portName);
    void close();

    bool write(QByteArray arr);

    void getAvailablePorts();
private:
    QSerialPort *serial;

    bool readResponce();

signals:
    void newData(QByteArray data);
    void availablePorts(QList<QString> ports);
    void stateChanged(bool state);
};

#endif // SERIALPORT_H
