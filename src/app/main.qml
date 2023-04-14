import QtQuick
import QtQuick.Controls 6.3

Window {
    id: root
    width: 1280
    height: 720
    // make main window non-resizable
    minimumWidth: width
    minimumHeight: height
    maximumWidth: width
    maximumHeight: height
    visible: true
    title: qsTr("ArtNet Tool")
    color: "White"

    Row{
        spacing: 1

        SideBar{
            id: sideBar
            width: 200
            height: root.height
        }

        DiscoveryView{
            height: root.height
            width: 1080
            visible: sideBar.selectionIndex == 0
        }
    }
}

//    Button {
//        id: button
//        x: 257
//        y: 219
//        width: 126
//        height: 43
//        text: qsTr("Discover")

//        onClicked:
//        {
//            devicefinder.discoverDevices()
//        }
//    }

//    Text {
//        id: text1
//        x: 257
//        y: 172
//        text: qsTr("Devices Found:")
//        font.pixelSize: 12
//    }

//    Text {
//        id: devicesCount
//        x: 400
//        y: 172
//        text: qsTr("0")
//        font.pixelSize: 12

//        Connections{
//            target: devicefinder
//            function onDeviceFound(total) {
//                devicesCount.text = total;
//                console.log(total);
//            }
//        }
//    }

//    TableView {
//        id: artpollReplyTable
//        anchors.fill: parent
////        columnSpacing: 1
////        rowSpacing: 1
//        clip: true
//        model: ArtpollReplyTableModel{
//            devices: devicefinder
//        }

//        delegate: Rectangle {
//            antialiasing: true
//            implicitWidth: 150
//            implicitHeight: 50
//            border.width: 0.5
//            border.color: "#616060"
//            color: root.color

//            Text {
//                text: display
//                anchors.centerIn: parent
//                color: "white"
//            }

////            Text {
////                text: model.fw
////                anchors.centerIn: parent
////            }
//        }
//    }

//    HorizontalHeaderView {
//        id: horizontalHeader
//        syncView: artpollReplyTable
//        anchors.left: artpollReplyTable.left
//    }
//}
