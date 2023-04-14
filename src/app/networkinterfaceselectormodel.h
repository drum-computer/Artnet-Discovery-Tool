#ifndef NETWORKINTERFACESELECTORMODEL_H
#define NETWORKINTERFACESELECTORMODEL_H

#include <QObject>


Q_MOC_INCLUDE("networkinterfaceselector.h")

class NetworkInterfaceSelector;

class NetworkInterfaceSelectorModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NetworkInterfaceSelector* networkInterfaceSelector
               READ networkInterfaceSelector
               WRITE setnetworkInterfaceSelector CONSTANT)
    Q_PROPERTY(QStringList interfaces READ interfaces CONSTANT)

public:
    explicit NetworkInterfaceSelectorModel(QObject *parent = nullptr);

    // Connect to backend
    NetworkInterfaceSelector *networkInterfaceSelector() const;
    void setnetworkInterfaceSelector(
            NetworkInterfaceSelector *networkInterfaceSelector);
    // list of strings in form of interface_name: ipv4
    QStringList interfaces();

public slots:
    void changeActiveInterface(int index);


private:
    NetworkInterfaceSelector *m_networkInterfaceSelector;
    QStringList m_interfaces{};

signals:

};

#endif // NETWORKINTERFACESELECTORMODEL_H
