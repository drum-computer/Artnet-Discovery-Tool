#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = nullptr);
    quint64 writeData(const QNetworkDatagram &datagram);
    void bindToAddress(const QHostAddress ip, const int port);

signals:
    // emitted on every new datagram
    void datagramReceived(char *datagram, qsizetype size, QHostAddress source_ip);

private slots:
    void processPendingDatagrams();

private:
    // udp socket to handle communication
    QUdpSocket m_udpSocket;
};

#endif // UDPSERVER_H
