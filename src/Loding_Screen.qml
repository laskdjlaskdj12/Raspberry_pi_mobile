import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
//import QtQuick.Controls.Styles 1.0
import QtQuick.Controls.Material 2.1

Rectangle_Design_Form{
    property alias loading_next_button: loading_button

    Item{

        id: rectangle

        Text {
            id: boiler_icon
            x: 52
            y: 45
            text: qsTr("TempTure")
            anchors.verticalCenterOffset: 1
            anchors.horizontalCenterOffset: 0
            font.pointSize: 60
            fontSizeMode: Text.VerticalFit
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Button{
            id:loading_button
            x: 41
            y: 393
            width: 294
            height: 125
            text: qsTr("Next")
            highlighted: true

            //Material.accent: Material.Pink
        }
    }
}
