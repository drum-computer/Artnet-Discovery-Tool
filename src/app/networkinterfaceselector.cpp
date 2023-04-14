#include "networkinterfaceselector.h"
#include <QtNetwork>
#include "artnettoolutils.h"


NetworkInterfaceSelector::NetworkInterfaceSelector(UdpServer* udpServer,
                                                   QObject *parent)
    : QObject{parent}
{
    m_udpServer = udpServer;
    // take list of all available interfaces and all available ip's
    // and return a list of interfaces that can be used for the
    // purposes of this app
    m_usableNetworkInterfaces = ArtnetToolUtils::get_usable_interfaces(
                QNetworkInterface::allInterfaces());
    foreach (auto i, m_usableNetworkInterfaces) {
        qInfo() << i.name;
        qInfo() << i.ip.toString();
        qInfo() << "______________";
    }
    // we always should have at least one usable
    // network interface at the start of the program
    assert(m_usableNetworkInterfaces.size() > 0);
    // choose first usable network interface as
    // the active one
    setActiveInterface(m_usableNetworkInterfaces.at(0));
}

QList<ArtnetToolUtils::UsableNetworkInterface>
NetworkInterfaceSelector::usableNetworkInterfaces() const
{
    return m_usableNetworkInterfaces;
}

ArtnetToolUtils::UsableNetworkInterface
NetworkInterfaceSelector::activeInterface() const
{
    return m_activeInterface;
}

void
NetworkInterfaceSelector::setActiveInterface(
        ArtnetToolUtils::UsableNetworkInterface newActiveInterface)
{
    m_activeInterface = newActiveInterface;
    m_udpServer->bindToAddress(m_activeInterface.ip,
                               ArtnetToolUtils::artnetNetworkPort);
}
