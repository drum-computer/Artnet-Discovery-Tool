#include "devicefinder.h"
#include "artnettoolutils.h"
#include <QDebug>

DeviceFinder::DeviceFinder(UdpServer *udpServer, QObject *parent)
    : QObject{parent}
{
    m_udpServer = udpServer;
    // subscribe to new udp messages
    QObject::connect(m_udpServer, &UdpServer::datagramReceived,
                     this, &DeviceFinder::receiveData);
}

QVector<ArtNetStructs::ArtPollReply> DeviceFinder::artNetNodes() const
{
    return m_artnetNodes;
}

void DeviceFinder::discoverDevices()
{
    // first we need to delete all discovered nodes
    clearDevices();
    // then we need to send an artpoll request
    QNetworkDatagram artpoll_request_packet = ArtnetToolUtils::create_artpoll_packet(
                ArtnetToolUtils::artnetNetworkPort, m_broadcastAddress);
    m_udpServer->writeData(artpoll_request_packet);
}

void DeviceFinder::receiveData(char *data, qsizetype size, QHostAddress source_ip)
{
    if (!ArtnetToolUtils::data_is_artpoll_reply_(data, size))
    {
        return;
    }
    ArtNetStructs::ArtPollReply *artpoll_reply =
            reinterpret_cast<ArtNetStructs::ArtPollReply*>(data);
    // TODO: potentially we need to check if we already
    // have this ip address in the list
    // add device reply to the list of discovered devices
    m_addNode(*artpoll_reply);
}

void DeviceFinder::m_addNode(ArtNetStructs::ArtPollReply node)
{
    emit preDeviceAppended();

    m_artnetNodes.emplaceBack(node);

    emit postDeviceAppended();
    emit numDeviceChanged(m_artnetNodes.size());
}

void DeviceFinder::clearDevices()
{
    // removes all rows from table
    for (int i = 0; i < m_artnetNodes.size(); i++) {
       emit preDeviceRemoved(i);
       emit postDeviceRemoved();

    }
    // deletes all devices
    m_artnetNodes.clear();
    emit numDeviceChanged(m_artnetNodes.size());
}
