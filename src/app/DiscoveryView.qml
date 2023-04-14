import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ArtpollReplyTableModel 1.0
import NetworkInterfaceSelectorModel 1.0

Item {
    id: root

    property int devicesFound: 0

    FontLoader { id: mainFont; source: "qrc:fonts/OpenSans-Regular.ttf" }

    NetworkInterfaceSelectorModel{
        id: networkInterfaces
        networkInterfaceSelector: NetworkInterfaceSelector
    }

    Connections{
        target: DeviceFinder
        function onNumDeviceChanged(total) {
            root.devicesFound = total;
        }
    }


    ColumnLayout{
        id: col
        anchors.fill: parent
        anchors.margins: 2
        spacing: 0

        // Controls on top of the table
        GroupBox{
            id: controls
            Layout.fillWidth: true
            background: Rectangle{border.width: 0}


            RowLayout
            {
                spacing: 20

                Button{
                    text: "Discover"
                    font.family: mainFont.name
                    font.weight: Font.DemiBold
                    Layout.leftMargin: 25
                    onClicked: {
                        DeviceFinder.discoverDevices();
                    }
                }

                Text{
                    text: ("devices found: " + root.devicesFound)
                    font.family: mainFont.name
                    color: "Black"
                    font.weight: Font.Normal
                }
                Text{
                    text: "Network interface"
                    font.family: mainFont.name
                    color: "Black"
                    font.weight: Font.Normal
                    Layout.leftMargin: 200
                }

                ComboBox{
                    id: interfaceSelector
                    implicitContentWidthPolicy: ComboBox.WidestText
                    Component.onCompleted: model = networkInterfaces.interfaces
                    onActivated: networkInterfaces.changeActiveInterface(currentIndex)
                }
            }
        }

        // Main discovery table
        HorizontalHeaderView {
            id: horizontalHeader
            syncView: artpollReplyTable
            Layout.fillWidth: true
            height: 50
            clip: true
            boundsBehavior: Flickable.StopAtBounds



            delegate: Rectangle {
                id: headerViewDelegate
                implicitWidth: 150
                implicitHeight: 50
                border.width: 0
                color: "#E1E1E1"

                HoverHandler {
                    id: mouse
                    acceptedDevices: PointerDevice.Mouse
                    cursorShape: Qt.PointingHandCursor
                }

                ToolTip {
                    id: headerTooltip
                    delay: 200
                    timeout: 0
                    visible: mouse.hovered
                    text: toolTip
                    implicitWidth: parent.width
                }

                Text {
                    text: display
                    anchors.centerIn: parent
                    color: "black"
                    font.family: mainFont.name
                    font.weight: Font.Normal
                }
            }
        }

        TableView {
            id: artpollReplyTable
            width: parent.width
            Layout.fillWidth: true
            height: (root.height - (controls.height + horizontalHeader.height))
            clip: true
            boundsBehavior: Flickable.StopAtBounds

            model: ArtpollReplyTableModel{
                deviceFinder: DeviceFinder
            }

            delegate: Rectangle {
                implicitWidth: 150
                implicitHeight: 50
                border.width: 1
                border.color: "#d9d9d9"
                color: "white"

                Text {
                    text: display
                    anchors.centerIn: parent
                    color: "black"
                    font.family: mainFont.name
                    font.weight: Font.DemiBold
                    font.pixelSize: 10
                }
            }
            ScrollBar.horizontal: ScrollBar{}
            ScrollBar.vertical: ScrollBar{}
        }
    }
}
