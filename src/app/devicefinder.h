#ifndef DEVICEFINDER_H
#define DEVICEFINDER_H

#include <QObject>
#include <QtNetwork>
#include "udpserver.h"
#include "artnettoolutils.h"

class DeviceFinder : public QObject
{
    Q_OBJECT

public:
    explicit DeviceFinder(UdpServer *udpServer, QObject *parent = nullptr);

    // database of all found artnet nodes
    QVector<ArtNetStructs::ArtPollReply> artNetNodes() const;

signals:
    // needed for model
    // to function properly
    void preDeviceAppended();
    void postDeviceAppended();
    void preDeviceRemoved(int index);
    void postDeviceRemoved();
    // emitted every time new artnet
    // node is found
    void numDeviceChanged(const int total);

public slots:
    // listen to new datagrams from udp server
    void receiveData(char *data, qsizetype size, QHostAddress source_ip);
    void discoverDevices();
    void clearDevices();


private:
    QHostAddress m_broadcastAddress{ArtnetToolUtils::broadcastAddress};
    UdpServer *m_udpServer;
    QVector<ArtNetStructs::ArtPollReply> m_artnetNodes;
    void m_addNode(ArtNetStructs::ArtPollReply node);
};

#endif // DEVICEFINDER_H
