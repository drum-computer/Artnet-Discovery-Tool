#include "udpserver.h"
#include <QUdpSocket>
#include <QDebug>


UdpServer::UdpServer(QObject *parent)
    : QObject{parent}, m_udpSocket(this)
{
    // this will allow to read new packets
    // as soon as they come in
    connect(&m_udpSocket, &QUdpSocket::readyRead,
            this, &UdpServer::processPendingDatagrams);
}

quint64 UdpServer::writeData(const QNetworkDatagram &datagram)
{
    // returns number of bytes written
    return m_udpSocket.writeDatagram(datagram);
}

void UdpServer::bindToAddress(const QHostAddress ip, const int port)
{
    //Unbind the socket if currently bound
    if(m_udpSocket.state() == QAbstractSocket::BoundState)
    {
        m_udpSocket.close();
    }
    // bind to new address
    m_udpSocket.bind(ip, port);
}

void UdpServer::processPendingDatagrams()
{
    // reads datagram and emits its content
    // as a signal
    QByteArray datagram;
    QHostAddress source_ip;

    while (m_udpSocket.hasPendingDatagrams()) {
        // resize byte array to the size of th eincoming datagram
        datagram.resize(int(m_udpSocket.pendingDatagramSize()));
        m_udpSocket.readDatagram(datagram.data(), datagram.size(), &source_ip);
        // notify listeners
        emit datagramReceived(datagram.data(), datagram.size(), source_ip);
    }
}
