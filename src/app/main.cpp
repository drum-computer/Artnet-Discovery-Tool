#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QQuickStyle>

#include "devicefinder.h"
#include "udpserver.h"
#include "networkinterfaceselector.h"
#include "artpollreplytablemodel.h"
#include "networkinterfaceselectormodel.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Basic");
    // initialize a udp server
    UdpServer udpServer;
    // initializize networkInterfaceSelector
    // that will get the list of usable interfaces
    // upon initialization, and elect the first one to be active
    NetworkInterfaceSelector networkInterfaceSelector(&udpServer);
    // initialize device finder
    DeviceFinder deviceFinder(&udpServer);

    QQmlApplicationEngine engine;

    // make devicefinder accessible to the frontend
    engine.rootContext()->setContextProperty("DeviceFinder", &deviceFinder);
    // make NetworkInterfaceSelector accessible to the frontend
    engine.rootContext()->setContextProperty(
                "NetworkInterfaceSelector", &networkInterfaceSelector);
    // register a type so we can instantiate it on the frontend
    qmlRegisterType<ArtpollReplyTableModel>("ArtpollReplyTableModel", 1, 0,
                                            "ArtpollReplyTableModel");
    // register a type so we can instantiate it on the frontend
    qmlRegisterType<NetworkInterfaceSelectorModel>(
                "NetworkInterfaceSelectorModel", 1, 0,
                "NetworkInterfaceSelectorModel");

    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
