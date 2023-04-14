import QtQuick
import QtQuick.Controls

Button {
    id: control
    text: qsTr("Button")
    width: parent.width
    anchors.left: parent.left
    anchors.right: parent.right
    checkable: true
    autoExclusive: true

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.checked ? "White" : "Black"
        verticalAlignment: Text.AlignVCenter
        leftPadding: 20

    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: control.checked ? 1.0 : 0.0
        color: control.checked ? "#3d3d3d" : "White"
        radius: 2

//        border.color: control.checked ? "#17a81a" : "#21be2b"
//       border.width: 1
//        radius: 2
//        color: "Blue"
    }
}
