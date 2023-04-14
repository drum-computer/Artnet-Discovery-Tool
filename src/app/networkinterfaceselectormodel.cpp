#include "networkinterfaceselectormodel.h"
#include "networkinterfaceselector.h"

NetworkInterfaceSelectorModel::NetworkInterfaceSelectorModel(QObject *parent)
    : QObject{parent}
{
    qInfo() << "NetworkInterfaceSelectorModel ctor";
}

NetworkInterfaceSelector
*NetworkInterfaceSelectorModel::networkInterfaceSelector() const
{
    return m_networkInterfaceSelector;
}

void NetworkInterfaceSelectorModel::setnetworkInterfaceSelector(
        NetworkInterfaceSelector *networkInterfaceSelector)
{
    qInfo() << "setting NetworkInterfaceSelector";
    m_networkInterfaceSelector = networkInterfaceSelector;
}

QStringList NetworkInterfaceSelectorModel::interfaces()
{
    qInfo() << "getting list of interfaces";

    QStringList interface_data{};
    if(!m_networkInterfaceSelector)
    {
        return interface_data;
    }
    foreach(auto i, m_networkInterfaceSelector->usableNetworkInterfaces())
    {
        interface_data.append(QString("%1:%2").arg(i.name, i.ip.toString()));
    }
    return interface_data;
}

void NetworkInterfaceSelectorModel::changeActiveInterface(int index)
{
    if(!m_networkInterfaceSelector)
    {
        return;
    }
    // changes active interface to be the interaface at index "index"
    // note this assumes 1 to 1 correspondency between list of usable
    // interfaces structs and list of physical interfaces returned by
    // the allInterfaces()
    m_networkInterfaceSelector->setActiveInterface(
        m_networkInterfaceSelector->usableNetworkInterfaces().at(index));

    qInfo() << "changing active index to:" << index;
}
