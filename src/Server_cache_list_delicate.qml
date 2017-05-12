import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQml.Models 2.2

Rectangle {

    property string color_string :panel_states_color
    property string ip_text :panel_ip

    id: server_list_delicate1
    x: 0
    y: 130
    width: 200
    height: 32

    Text {
        id: text2
        x: 16
        y: 0
        width: 129
        height: 32
        text: panel_ip
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 18

        Rectangle {
            x: 150
            y: 4
            width: 25
            height: 24
            color: panel_states_color
            radius: width*0.5
        }
    }
}


