#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MainWindow mainWindow;
    engine.rootContext()->setContextProperty("mainWindow", &mainWindow);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
