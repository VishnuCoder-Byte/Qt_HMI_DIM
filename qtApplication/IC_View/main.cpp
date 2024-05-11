#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "subscriptionmanager.h"
#include <QQmlContext>
#include <QtQuick>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/IC_View/main.qml"_qs);
    SubscriptionManager obj;
    engine.rootContext()->setContextProperty("subscriber",&obj);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
