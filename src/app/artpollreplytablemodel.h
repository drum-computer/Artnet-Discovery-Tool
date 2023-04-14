#ifndef ARTPOLLREPLYTABLEMODEL_H
#define ARTPOLLREPLYTABLEMODEL_H

#include <Qt>
#include <QAbstractTableModel>

Q_MOC_INCLUDE("devicefinder.h")

class DeviceFinder;

class ArtpollReplyTableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(DeviceFinder* deviceFinder READ deviceFinder WRITE setDeviceFinder CONSTANT)

public:
    explicit ArtpollReplyTableModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // Data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const override;

    // Connect to backend
    DeviceFinder *deviceFinder() const;
    void setDeviceFinder(DeviceFinder *deviceFinder);

    virtual QHash<int, QByteArray> roleNames() const override;

private:
    DeviceFinder *m_deviceFinder;
    QStringList header_data{   "Ip Address",
                               "Port",
                               "Version",
                               "Net Switch",
                               "Sub Switch",
                               "OEM",
                               "Ubea",
                               "Status1",
                               "Esta Man",
                               "Short Name",
                               "Long Name",
                               "Node Report",
                               "Num Ports",
                               "Port Types",
                               "Good Input",
                               "Good Output a",
                               "Sw In",
                               "Sw Out",
                               "Acn Priority",
                               "Sw Macro",
                               "Sw Remote",
                               "Style",
                               "Mac",
                               "Bind Ip",
                               "Bind Index",
                               "Status2",
                               "Good Output b",
                               "Status3",
                               "Default Resp Uid"
                           };
    // all textual information should be combined in some kind of struct probably
    QStringList header_tooltip_data{
        //"Ip Address"
        "Node’s IP address",
        //"Port"
        "The Port is always 6454 in Artnet",
        //"Version"
        "Node’s firmware revision number",
        //NetSwitch
        "Bits 14-8 of the 15 bit Port-Address"
        " are encoded into the bottom 7 bits"
        " of this field. This is used in combination"
        " with SubSwitch and SwIn[] or SwOut[] to produce"
        " the full universe address",
        //"Sub Switch",
        "Bits 7-4 of the 15 bit Port-Address are"
        " encoded into the bottom 4 bits of this field."
        " This is used in combination with NetSwitch"
        " and SwIn[] or SwOut[] to produce the full"
        " universe address.",
        //"OEM"
        "The Oem word describes the equipment"
        " vendor and the feature set available. Bit 15"
        " high indicates extended features available",
        //"Ubea"
        "This field contains the firmware version of"
        " the User Bios Extension Area (UBEA). If the"
        " UBEA is not programmed, this field contains"
        " zero.",
        //"Status1"
        "General Status register containing bit fields"
        " as follows."
        "\n7-6 Indicator state."
        "\n00 Indicator state unknown."
        "\n01 Indicators in Locate / Identify"
        " Mode."
        "\n10 Indicators in Mute Mode."
        "\n11 Indicators in Normal Mode."
        "\n\n5-4 Port-Address Programming Authority"
        "\n00 Port-Address Programming"
        " Authority unknown."
        "\n01 All Port-Address set by front panel"
        " controls."
        "\n10 All or part of Port-Address"
        " programmed by network or Web"
        " browser."
        "\n11 Not used."
        "\n3 Not implemented, transmit as zero,"
        " receivers do not test."
        "\n2\n0 = Normal firmware boot (from flash)."
        " Nodes that do not support dual boot, clear"
        " this field to zero."
        "\n1 = Booted from ROM."
        "\n1\n0 = Not capable of Remote Device"
        " Management (RDM)."
        "\n1 = Capable of Remote Device Management"
        " (RDM)."
        "\n0\n0 = UBEA not present or corrupt"
        "\n1 = UBEA present",
        //"Esta Man"
        "The ESTA manufacturer code. These codes"
        " are used to represent equipment"
        " manufacturer. They are assigned by ESTA."
        " This field can be interpreted as two ASCII"
        " bytes representing the manufacturer initials.",
        //"Short Name"
        "Short name for the node",
        //"Long Name"
        "Long name for the node",
        //"Node Report"
        "Currently not implemented",
        //"Num Ports"
        "Number of input and output ports",
        //"Port Types"
        "This array defines the operation and"
        " protocol of each channel. (A product with 4"
        " inputs and 4 outputs would report 0xc0,"
        " 0xc0, 0xc0, 0xc0). The array length is fixed,"
        " independent of the number of inputs or"
        " outputs physically available on the Node."
        "\n\n7 Set is this channel can output data from the"
        " Art-Net Network."
        "\n6 Set if this channel can input onto the Art-Net"
        " Network."
        "\n5-0 000000 = DMX512"
        "\n000001 = MIDI"
        "\n000010 = Avab"
        "\n000011 = Colortran CMX"
        "\n000100 = ADB 62.5"
        "\n000101 = Art-Net"
        "\n000110 = DALI",
        //"Good Input"
        "This array defines input status of the node."
        "\n\n7 Set – Data received."
        "\n6 Set – Channel includes DMX512 test"
        " packets."
        "\n5 Set – Channel includes DMX512 SIP’s."
        "\n4 Set – Channel includes DMX512 text"
        " packets."
        "\n3 Set – Input is disabled."
        "\n2 Set – Receive errors detected."
        "\n1-0 Unused and transmitted as zero.",
        //"Good Output a"
        "This array defines output status of the node."
        "\n\n7 Set – Data is being transmitted."
        "\n6 Set – Channel includes DMX512 test"
        " packets."
        "\n5 Set – Channel includes DMX512 SIP’s."
        "\n4 Set – Channel includes DMX512 text"
        " packets."
        "\n3 Set – Output is merging ArtNet data."
        "\n2 Set – DMX output short detected on power"
        " up"
        "\n1 Set – Merge Mode is LTP."
        "\n0 Set – Output is selected to transmit sACN."
        " Clr – Output is selected to transmit Art-Net.",
        //"Sw In"
        "Bits 3-0 of the 15 bit Port-Address for each"
        " of the 4 possible input ports are encoded"
        " into the low nibble.",
        //"Sw Out"
        "Bits 3-0 of the 15 bit Port-Address for each"
        " of the 4 possible output ports are encoded"
        " into the low nibble.",
        //"Acn Priority"
        "The sACN priority value that will be used"
        " when any received DMX is converted to"
        " sACN.",
        //"Sw Macro"
        " If the Node supports macro key inputs, this"
        " byte represents the trigger values. The Node"
        " is responsible for ‘debouncing’ inputs. When"
        " the ArtPollReply is set to transmit"
        " automatically, (Flags Bit 1), the ArtPollReply"
        " will be sent on both key down and key up"
        " events. However, the Controller should not"
        " assume that only one bit position has"
        " changed."
        " The Macro inputs are used for remote event"
        " triggering or cueing."
        " Bit fields are active high."
        "\n7 Set – Macro 8 active."
        "\n6 Set – Macro 7 active."
        "\n5 Set – Macro 6 active."
        "\n4 Set – Macro 5 active."
        "\n3 Set – Macro 4 active."
        "\n2 Set – Macro 3 active."
        "\n1 Set – Macro 2 active."
        "\n0 Set – Macro 1 active.",
        //"Sw Remote"
        "If the Node supports remote trigger inputs,"
        " this byte represents the trigger values. The"
        " Node is responsible for ‘debouncing’ inputs."
        " When the ArtPollReply is set to transmit"
        " automatically, (Flags Bit 1), the ArtPollReply"
        " will be sent on both key down and key up"
        " events. However, the Controller should not"
        " assume that only one bit position has"
        " changed."
        " The Remote inputs are used for remote"
        " event triggering or cueing."
        " Bit fields are active high."
        "\n7 Set – Remote 8 active."
        "\n6 Set – Remote 7 active."
        "\n5 Set – Remote 6 active."
        "\n4 Set – Remote 5 active."
        "\n3 Set – Remote 4 active."
        "\n2 Set – Remote 3 active."
        "\n1 Set – Remote 2 active."
        "\n0 Set – Remote 1 active",
        //"Style"
        "The Style code defines the equipment style"
        " of the device.",
        //"Mac"
        "MAC address of the node",
        //"Bind Ip"
        "If this unit is part of a larger or modular"
        " product, this is the IP of the root device.",
        //"Bind Index"
        "This number represents the order of bound"
        " devices. A lower number means closer to"
        " root device. A value of 1 means root device",
        //"Status2"
        "0 Set = Product supports web browser"
        " configuration."
        "\n1 Clr = Node’s IP is manually configured."
        " Set = Node’s IP is DHCP configured."
        "\n2 Clr = Node is not DHCP capable."
        " Set = Node is DHCP capable."
        "\n3 Clr = Node supports 8-bit Port-Address (ArtNet II)."
        " Set = Node supports 15-bit Port-Address"
        " (Art-Net 3 or 4)."
        "\n4 Clr = Node not able to switch between ArtNet and sACN."
        " Set = Node is able to switch between ArtNet and sACN."
        "\n5 Clr = Not squawking."
        " Set = squawking."
        "\n6 Clr = Node does not support switching of"
        " output style using ArtAddress."
        " Set = Node supports switching of output"
        " style using ArtAddress."
        "\n7 Clr = Node does not support control of RDM"
        " using ArtAddress."
        " Set = Node supports control of RDM using"
        " ArtAddress.",
        //"Good Output b"
        "This array defines output status of the node."
        "\n7 Set – RDM is disabled."
        " Clr – RDM is enabled."
        "\n6 Set – Output style is continuous"
        " Clr – Output style is delta."
        "\n5 Not used, set to zero"
        "\n4 Not used, set to zero"
        "\n3 Not used, set to zero"
        "\n2 Not used, set to zero"
        "\n1 Not used, set to zero"
        "\n0 Not used, set to zero",
        //"Status3",
        "General Status register containing bit fields"
        " as follows."
        "\n7-6 Failsafe state. How the node behaves in the"
        " event that network data is lost."
        " 00 Hold last state."
        " 01 All outputs to zero."
        " 10 All outputs to full."
        " 11 Playback fail safe scene."
        "\n5 Set – Node supports fail-over."
        " Clr – Node does not support fail-over."
        "\n4 Set – Node supports LLRP."
        " Clr – Node does not support LLRP."
        "\n3 Set – Node supports switching ports"
        " between input and output. (PortTypes[]"
        " shows the current direction)"
        " Clr – Node does not support switching port"
        " direction."
        "\n2 Not used, set to zero"
        "\n1 Not used, set to zero"
        "\n0 Not used, set to zero",
        //"Default Resp Uid"
        "RDMnet & LLRP Default Responder UID"
    };
};

#endif // ARTPOLLREPLYTABLEMODEL_H
