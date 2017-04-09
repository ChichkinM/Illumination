#include <QCoreApplication>
#include <QCommandLineParser>
#include "mainobj.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainObj *obj = new MainObj();

    QCommandLineParser clParser;
    clParser.addHelpOption();

    QCommandLineOption comPortOpt("com", "Имя COM порта. Если введено не корректое значение "
                                         "или данная опция отсутствует, то будет произведен автоматический "
                                         "поиск устройства", "comPortOpt");
    clParser.addOption(comPortOpt);

    clParser.process(a);


    bool convert = false;
    int comNumber = clParser.value(comPortOpt).toInt(&convert);
    QString  comName = QString("COM%1").arg(comNumber);

    emit obj->networkOpen();
    if(convert)
        obj->openSerialPort(comName);
    else
        obj->openSerialPort();

    return a.exec();
}
