import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
//import QtQuick.Controls.Material 2.1


Rectangle_Design_Form {
    property alias to_menu_back_button: account_to_menu_button

    Item{
        id: account_info_panel
        //Material.theme: Material.Dark
        Rectangle {
            id: menu_bar
            x: 0
            y: 0
            width: 374
            height: 86
            color: "#ffffff"
            radius: 4

            Rectangle {
                id: back_button
                x: 0
                y: 0
                width: 121
                height: 86
                color: "#ff8000"
                MouseArea{
                    id:account_to_menu_button
                    x: 0
                    y: 0
                    width: parent.width
                    height: parent.height
                }
            }
        }

        Rectangle {
            id: account_rectangle
            x: 251
            y: 23
            width: 111
            height: 98
            color: "#ffffff"
            radius: 10
        }

        Label {
            id: owner_hash
            x: 22
            y: 400
            text: qsTr("Hash")
            Layout.preferredHeight: 58
            Layout.preferredWidth: 98
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            id: device_name
            x: 22
            y: 231
            text: qsTr("Name")
            Layout.preferredHeight: 58
            Layout.preferredWidth: 98
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: device_name_field
            x: 126
            y: 231
            width: 236
            height: 58
            Layout.preferredHeight: 58
            Layout.preferredWidth: 450
            horizontalAlignment: Text.AlignHCenter
            readOnly: true
        }

        TextField {
            id: owner_hash_field
            x: 126
            y: 400
            width: 236
            height: 58
            Layout.preferredHeight: 58
            Layout.preferredWidth: 450
            horizontalAlignment: Text.AlignHCenter
            readOnly: true
        }

        Label {
            id: device_count
            x: 22
            y: 308
            text: qsTr("Device")
            Layout.preferredHeight: 58
            Layout.preferredWidth: 98
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: device_count_field
            x: 125
            y: 308
            width: 237
            height: 58
            Layout.preferredHeight: 58
            Layout.preferredWidth: 450
            horizontalAlignment: Text.AlignHCenter
            readOnly: true
        }

    }

}
