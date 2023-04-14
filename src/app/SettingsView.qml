import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    FontLoader { id: mainFont; source: "qrc:fonts/OpenSans-Regular.ttf" }

    ColumnLayout{
        id: col
        anchors.fill: parent
        anchors.margins: 2
        spacing: 0

        GroupBox{
            id: controls
            Layout.fillWidth: true
            background: Rectangle{border.width: 0}
            Layout.alignment: Qt.AlignTop

            RowLayout
            {
                spacing: 20

                Text{
                    text: "Network interface"
                    font.family: mainFont.name
                    color: "Black"
                    font.weight: Font.Normal
                }

                ComboBox{
                    id: interfaceSelector
                    model: ["wifi", "ethernet1", "ethernet2"]
                }
            }
        }
    }
}
