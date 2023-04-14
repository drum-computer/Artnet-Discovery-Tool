#ifndef NETWORKINTERFACESELECTOR_H
#define NETWORKINTERFACESELECTOR_H

#include <QObject>
#include <QtNetwork>
#include "artnettoolutils.h"
#include "udpserver.h"



class NetworkInterfaceSelector : public QObject
{
    // This class manages everything
    // related to the network interfaces
    // available to use on the machine
    Q_OBJECT
public:
    explicit NetworkInterfaceSelector(UdpServer* udpServer,
                                      QObject *parent = nullptr);
    // list of all network interfaces that can be used by the app
    // read-only
    QList<ArtnetToolUtils::UsableNetworkInterface> usableNetworkInterfaces() const;

    ArtnetToolUtils::UsableNetworkInterface activeInterface() const;
    void setActiveInterface(
            ArtnetToolUtils::UsableNetworkInterface newActiveInterface);

private:
    UdpServer *m_udpServer;
    ArtnetToolUtils::UsableNetworkInterface m_activeInterface{};
    QList<ArtnetToolUtils::UsableNetworkInterface> m_usableNetworkInterfaces{};

signals:

};

#endif // NETWORKINTERFACESELECTOR_H
