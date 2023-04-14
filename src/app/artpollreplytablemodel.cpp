#include "artpollreplytablemodel.h"
#include "devicefinder.h"

namespace{
    // helper functions
    const QStringList device_to_string(const ArtNetStructs::ArtPollReply& device)
    {
        QStringList answer;
        // takes a "raw" artpoll reply and returns a list of strings
        // each string being one field of the reply.
        // The idea is to convert raw data to a human-presentable format
        answer.append(QString("%1.%2.%3.%4").arg(device.ip_address[0])
                                                   .arg(device.ip_address[1])
                                                   .arg(device.ip_address[2])
                                                   .arg(device.ip_address[3]));
        answer.append(QString::number(device.port));
        answer.append(QString("%1.%2").arg(device.ver_info_hi)
                                      .arg(device.ver_info_lo));
        answer.append(QString::number(device.net_switch));
        answer.append(QString::number(device.sub_switch));
        answer.append(QString::number(device.oem_hi * 256 + device.oem));
        answer.append(QString::number(device.ubea));
        answer.append(QString("%1").arg(device.status1, 8, 2, QLatin1Char('0')));
        answer.append(QString::number(device.esta_man_hi * 256 + device.esta_man_lo));
        answer.append(QString(device.short_name));
        answer.append(QString(device.long_name));
        answer.append(QString("0")); // node report is not yet implemented
        answer.append(QString::number(device.num_ports_hi * 256 + device.num_ports_lo));
        answer.append(QString("[0x%1, 0x%2, 0x%3, 0x%4]")
                                            .arg(QString::number(device.port_types[0], 16),
                                                 QString::number(device.port_types[1], 16),
                                                 QString::number(device.port_types[2], 16),
                                                 QString::number(device.port_types[3], 16)));
        answer.append(QString("[0x%1, 0x%2, 0x%3, 0x%4]")
                                            .arg(QString::number(device.good_input[0], 16),
                                                 QString::number(device.good_input[1], 16),
                                                 QString::number(device.good_input[2], 16),
                                                 QString::number(device.good_input[3], 16)));
        answer.append(QString("[0x%1, 0x%2, 0x%3, 0x%4]")
                                            .arg(QString::number(device.good_output_a[0], 16),
                                                 QString::number(device.good_output_a[1], 16),
                                                 QString::number(device.good_output_a[2], 16),
                                                 QString::number(device.good_output_a[3], 16)));
        answer.append(QString("[%1, %2, %3, %4]")
                                            .arg(QString::number(device.sw_in[0]),
                                                 QString::number(device.sw_in[1]),
                                                 QString::number(device.sw_in[2]),
                                                 QString::number(device.sw_in[3])));
        answer.append(QString("[%1, %2, %3, %4]")
                                            .arg(QString::number(device.sw_out[0]),
                                                 QString::number(device.sw_out[1]),
                                                 QString::number(device.sw_out[2]),
                                                 QString::number(device.sw_out[3])));
        answer.append(QString::number(device.acn_priority));
        answer.append(QString("%1").arg(device.sw_macro, 8, 2, QLatin1Char('0')));
        answer.append(QString("%1").arg(device.sw_remote, 8, 2, QLatin1Char('0')));
        answer.append(QString::number(device.style));
        answer.append(QString("%1:%2:%3:%4:%5:%6")
                                            .arg(QString::number(device.mac_hi, 16),
                                                 QString::number(device.mac_1, 16),
                                                 QString::number(device.mac_2, 16),
                                                 QString::number(device.mac_3, 16),
                                                 QString::number(device.mac_4, 16),
                                                 QString::number(device.mac_lo, 16)));
        answer.append(QString("%1.%2.%3.%4").arg(device.bind_ip[0])
                                                   .arg(device.bind_ip[1])
                                                   .arg(device.bind_ip[2])
                                                   .arg(device.bind_ip[3]));
        answer.append(QString::number(device.bind_index));
        answer.append(QString("%1").arg(device.status2, 8, 2, QLatin1Char('0')));
        answer.append(QString("[0x%1, 0x%2, 0x%3, 0x%4]")
                                            .arg(QString::number(device.good_output_b[0], 16),
                                                 QString::number(device.good_output_b[1], 16),
                                                 QString::number(device.good_output_b[2], 16),
                                                 QString::number(device.good_output_b[3], 16)));
        answer.append(QString("%1").arg(device.status3, 8, 2, QLatin1Char('0')));
        answer.append(QString("%1:%2:%3:%4:%5:%6")
                                            .arg(QString::number(device.default_resp_uid_hi, 16),
                                                 QString::number(device.default_resp_uid_1, 16),
                                                 QString::number(device.default_resp_uid_2, 16),
                                                 QString::number(device.default_resp_uid_3, 16),
                                                 QString::number(device.default_resp_uid_4, 16),
                                                 QString::number(device.default_resp_uid_lo, 16)));
        return answer;
    }
}

ArtpollReplyTableModel::ArtpollReplyTableModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_deviceFinder(nullptr)
{

}

int ArtpollReplyTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_deviceFinder)
        return 0;

    return m_deviceFinder->artNetNodes().size();
}

int ArtpollReplyTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_deviceFinder)
        return 0;

    return header_data.length();
}

QVariant ArtpollReplyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_deviceFinder || role != Qt::DisplayRole)
        return QVariant();

    // NOTE: this is better to do only once, rather than every lookup,
    // but it's more convenient to have it here, but it can be potentially
    // optimized if needed
    QStringList device_as_string = device_to_string(m_deviceFinder->artNetNodes().at(index.row()));
    if (index.column() >= device_as_string.length())
    {
        //qDebug() << "Ip address:" << device_as_string[0];
        return QString("");
    }
    return device_as_string[index.column()];
}


QVariant ArtpollReplyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // check data
    if ((orientation != Qt::Orientation::Horizontal)
        || !m_deviceFinder)
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        return QVariant(header_data[section]);
    }
    else if (role == Qt::ToolTipRole)
    {
        return QVariant(header_tooltip_data[section]);
    }
    // look up header data
    return QVariant();
}

DeviceFinder *ArtpollReplyTableModel::deviceFinder() const
{
    return m_deviceFinder;
}

void ArtpollReplyTableModel::setDeviceFinder(DeviceFinder *deviceFinder)
{
    beginResetModel();
    // check if we already had another instance of
    // device finder connected
    if (m_deviceFinder)
        m_deviceFinder->disconnect(this);
    // connect device finder to the model
    m_deviceFinder = deviceFinder;

    if (m_deviceFinder) {
        connect(m_deviceFinder, &DeviceFinder::preDeviceAppended, this, [=]() {
            const int index = m_deviceFinder->artNetNodes().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(m_deviceFinder, &DeviceFinder::postDeviceAppended, this, [=]() {
            endInsertRows();
        });

        connect(m_deviceFinder, &DeviceFinder::preDeviceRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(m_deviceFinder, &DeviceFinder::postDeviceRemoved, this, [=]() {
            endRemoveRows();
        });
    }
    endResetModel();
}

QHash<int, QByteArray> ArtpollReplyTableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"},
             {Qt::ToolTipRole, "toolTip"}};
}
