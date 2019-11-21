
#include "bridge.h"
#include "worker.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QtQml>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
//    const auto type = qmlRegisterType<Bridge>("com.apm.bridge",1,0,"Bridge");
    Bridge bridge;
    Worker worker;
    bridge.setWorker(&worker);
    auto context = engine.rootContext();
    if(context != nullptr)
    {
        context->setContextProperty("bridge",&bridge);
    }
    worker.start();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
