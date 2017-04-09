#include "serialport.h"

#include <QDebug>
#include <QSerialPortInfo>

#define WAIT_FOR_READY_READ 100

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{

    //    serial = new QSerialPort();

    //    connect(serial, SIGNAL(readyRead()), this, SLOT(readResponce()));
}

SerialPort::~SerialPort()
{
    close();
}

void SerialPort::getAvailablePorts()
{
    QList<QString> portNames;
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    foreach (QSerialPortInfo port, ports)
        portNames.append(port.portName());

    emit availablePorts(portNames);
}

void SerialPort::open(QString portName)
{
    serial = new QSerialPort();

    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);

    qDebug() << "open " << portName << serial->open(QIODevice::ReadWrite);

    emit stateChanged(serial->isOpen());
}

void SerialPort::close()
{
    serial->close();

    emit stateChanged(serial->isOpen());
}

//возможный мультипоточный вызов, но не ломается почему-то
bool SerialPort::write(QByteArray arr)
{
    if(serial->isOpen())
    {
        serial->write(arr);

        qDebug() << arr.toHex();

        readResponce();
    }
}

bool SerialPort::readResponce()
{
    QByteArray responce;
    while(serial->waitForReadyRead(WAIT_FOR_READY_READ))
        responce.append(serial->readAll());

    if(responce.size() > 0)
        emit newData(responce);
}

