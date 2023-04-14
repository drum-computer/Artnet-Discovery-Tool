#ifndef ARTNETTOOLUTILS_H
#define ARTNETTOOLUTILS_H
#include "qglobal.h"
#include <QtNetwork>


// all artnet packet descriptions
// live here
namespace ArtNetStructs {
    struct ArtPollRequest {
        char header[8]     { "Art-Net" };
        quint8 op_code_lo  { 0x00 };
        quint8 op_code_hi  { 0x20 };
        quint8 prot_ver_hi { 0x00 };
        quint8 prot_ver_lo { 0x0E };
        quint8 talk_to_me  { 0x00 };
        quint8 priority    { 0x10 };
        quint8 priority1   { 0x00 };
        quint8 priority2   { 0x00 };
        quint8 priority3   { 0x00 };
        quint8 priority4   { 0x00 };
    };

    struct ArtPollReply{
        char header[8]{};
        uint16_t opcode{0};
        uint8_t ip_address[4]{};
        uint16_t port{};
        uint8_t ver_info_hi{};
        uint8_t ver_info_lo{};
        uint8_t net_switch{};
        uint8_t sub_switch{};
        uint8_t oem_hi{};
        uint8_t oem{};
        uint8_t ubea{};
        uint8_t status1{};
        uint8_t esta_man_lo{};
        uint8_t esta_man_hi{};
        char short_name[18]{};
        char long_name[64]{};
        uint8_t node_report[64]{};
        uint8_t num_ports_hi{};
        uint8_t num_ports_lo{};
        uint8_t port_types[4]{};
        uint8_t good_input[4]{};
        uint8_t good_output_a[4]{};
        uint8_t sw_in[4]{};
        uint8_t sw_out[4]{};
        uint8_t acn_priority{};
        uint8_t sw_macro{};
        uint8_t sw_remote{};
        uint8_t spare1{};
        uint8_t spare2{};
        uint8_t spare3{};
        uint8_t style{};
        uint8_t mac_hi{};
        uint8_t mac_1{};
        uint8_t mac_2{};
        uint8_t mac_3{};
        uint8_t mac_4{};
        uint8_t mac_lo{};
        uint8_t bind_ip[4]{};
        uint8_t bind_index{};
        uint8_t status2{};
        uint8_t good_output_b[4]{};
        uint8_t status3{};
        uint8_t default_resp_uid_hi{};
        uint8_t default_resp_uid_1{};
        uint8_t default_resp_uid_2{};
        uint8_t default_resp_uid_3{};
        uint8_t default_resp_uid_4{};
        uint8_t default_resp_uid_lo{};
        uint8_t filler[15]{};
    };
}


namespace ArtnetToolUtils{

// this opcode always means artpoll reply
const int artpollReplyOpcode{0x2100};
// artnet communication should always use
// this port number
const int artnetNetworkPort{6454};
const char broadcastAddress[]{"255.255.255.255"};

    struct UsableNetworkInterface{
        // this is a handy struct
        // that groups all relevant
        // information about the
        // usable network interface
        QNetworkInterface   interface;
        QString             name;
        QHostAddress        ip;
    };

    static bool data_is_artpoll_reply_(char *data, qsizetype size)
    {
        // checks if data is artpoll reply
//        qInfo() << "size:" << size;
        // if the size of the received message
        // is different then we can return right away
        if (size > sizeof(ArtNetStructs::ArtPollReply))
        {
            return false;
        }
        // TODO: this is too risky, we need to do it
        // differently, but I don't know how yet
        ArtNetStructs::ArtPollReply *artpoll_reply =
                reinterpret_cast<ArtNetStructs::ArtPollReply*>(data);
        return artpoll_reply->opcode == artpollReplyOpcode;
    }

    static QNetworkDatagram create_artpoll_packet(const int port, const QHostAddress address)
    {
        // Helper method to create a packet
        // that we can send through udp socket

        // here we're converting struct to
        // a datagram packet. Note that it's
        // a bit risky to do it like that
        // because I'm assuming that all the
        // data in the struct is packed without
        // "holes"
        QByteArray packet;
        ArtNetStructs::ArtPollRequest artpollRequest;
        QDataStream in(&packet, QIODevice::WriteOnly);
        in.writeRawData((char*)&artpollRequest, sizeof(artpollRequest));
        QNetworkDatagram datagram(packet, address, port);
        return datagram;
    }

    static QList<QNetworkInterface> filter_unusable_interfaces(QList<QNetworkInterface>& interfaces)
    {
        // returns a list of Network interfaces that
        // can be used for the artnet operations
        QList<QNetworkInterface> usable_interfaces{};

        foreach (auto i, interfaces) {
            bool isUp = i.flags().testFlag(QNetworkInterface::IsUp);
            bool isRunning = i.flags().testFlag(QNetworkInterface::IsRunning);
            bool notLoopBack = !(i.flags().testFlag(QNetworkInterface::IsLoopBack));
            if(isUp && isRunning && notLoopBack // ignore non active devices
                    && (i.type() == QNetworkInterface::Ethernet // ignore non ethernet/wifi devices
                        || i.type() == QNetworkInterface::Wifi)
                    && i.addressEntries().size() > 0 // ignore devices with no address
              )
            {
                usable_interfaces.append(i);
            }
        }
        return usable_interfaces;
    }

    static bool address_is_ipv4(QNetworkAddressEntry& addressEntry)
    {
        static QRegularExpression re; // make sure we only construct object once
        re.setPattern("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
        QRegularExpressionMatch match = re.match(addressEntry.ip().toString());
        return match.hasMatch();
    }

    static QList<UsableNetworkInterface> get_usable_interfaces(QList<QNetworkInterface> interfaces)
    {
        // this function picks usable interfaces from all available
        // network interfaces and returns them as a list of structs
        // of type UsableNetworkInterface
        QList<UsableNetworkInterface> usableNetworkInterfaces{};
        // first let's remove all unusable interfaces from the list
        // of interfaces
        QList<QNetworkInterface> usableInterfaces = filter_unusable_interfaces(interfaces);
        // next let's gather all info and put it in structs
        // loop over each interface
        foreach(auto i, usableInterfaces)
        {
            // loop over each address
            // associated with that interface
            foreach(auto z, i.addressEntries())
            {
                // if it's ipv4 add this interface
                // to the list of usable interfaces
                if(address_is_ipv4(z))
                {
                    UsableNetworkInterface interface{};
                    interface.interface = i;
                    interface.name = i.humanReadableName();
                    interface.ip = z.ip();
                    usableNetworkInterfaces.push_back(interface);
                }
            }
        }
        return usableNetworkInterfaces;
    }
}

#endif // ARTNETTOOLUTILS_H
