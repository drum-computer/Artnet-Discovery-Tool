import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    FontLoader { id: sidenavfont; source: "qrc:fonts/OpenSans-Bold.ttf" }

    property int selectionIndex: 0

    Rectangle
    {
        id: background
        width: parent.width
        height: parent.height
        color: "#E1E1E1"

        Text{
            id: logo
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 140

            text: "Art-\nNet\nTool"
            font.pixelSize: 28
            wrapMode: Text.WordWrap
            font.bold: true
            font.family: "Verdana"
            leftPadding: 20
            topPadding: 20
            lineHeight: 0.75

        }

        Column{
            id: sidemenu
            spacing: 0
            height: 200
            width: background.width
            anchors.top: logo.bottom

            SideNavButton{
                text: "Discovery"
                font: sidenavfont.font
                checked: true
                onToggled: function(){ root.selectionIndex = 0 }
            }

//            SideNavButton{
//                text: "Configure"
//                font: sidenavfont.font
//                onToggled: function(){ root.selectionIndex = 1 }
//            }

//            SideNavButton{
//                text: "Backchannel"
//                font: sidenavfont.font
//                onToggled: function(){ root.selectionIndex = 2 }
//            }

//            SideNavButton{
//                text: "Firmware"
//                font: sidenavfont.font
//                onToggled: function(){ root.selectionIndex = 3 }
//            }

//            SideNavButton{
//                text: "Settings"
//                font: sidenavfont.font
//                onToggled: function(){ root.selectionIndex = 4 }
//            }

        }
    }
}
