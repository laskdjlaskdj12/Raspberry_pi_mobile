import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls.Material 2.1

Rectangle_Design_Form{
    property alias loading_next_button: loading_button
    id: rectangle
    width: 720
    height: 960

    Text {
        id: boiler_icon
        x: 224
        y: 445
        text: qsTr("TempTure")
        anchors.verticalCenterOffset: 1
        anchors.horizontalCenterOffset: 0
        font.pointSize: 60
        fontSizeMode: Text.VerticalFit
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "white"
    }

    Button{
        id:loading_button
        x: 213
        y: 740
        width: 294
        height: 125
        text: qsTr("Next")
    }
}
