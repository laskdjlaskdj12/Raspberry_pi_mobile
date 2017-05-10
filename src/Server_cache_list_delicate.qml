import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQml.Models 2.2

Rectangle {

    property string states_color

    width: 200
    height: 597

    Rectangle{
        id: server_list_delicate
        x: 0
        y: 83
        width: 200
        height: 32
        MouseArea{
            id: server_list_delicate_mouse_area
            width: parent.width
            height: parent.height
            onClicked: {

            }
        }

        Text {
            id: text1
            x: 0
            width: 200
            height: 32
            text: qsTr("127.0.0.1")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 20

            Rectangle{
                x: 167
                y: 4
                height: 24
                color: "#64e96b"
                width: 25
                radius: width*0.5
            }
        }
    }

    Rectangle {
        id: server_list_delicate1
        x: 0
        y: 130
        width: 200
        height: 32
        Text {
            id: text2
            x: 0
            width: 200
            height: 32
            text: qsTr("255.255.255.255")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
            Rectangle {
                x: 167
                y: 4
                width: 25
                height: 24
                color: "#e14747"
                radius: width*0.5
            }
        }

        MouseArea {
            id: server_list_delicate_mouse_area1
            x: 0
            y: 0
            width: parent.width
            height: parent.height
        }
    }
}
