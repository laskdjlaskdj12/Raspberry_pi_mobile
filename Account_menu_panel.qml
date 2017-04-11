import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.1


Rectangle_Design_Form {
    property alias to_menu_back_button: account_to_menu_button
    width: 720
    height: 960

    Item{
        id: account_info_panel
        Material.theme: Material.Dark
        Rectangle {
            id: menu_bar
            x: 0
            y: 0
            width: 720
            height: 111
            color: "#ffffff"
            radius: 4

            Rectangle {
                id: back_button
                x: 0
                y: 0
                width: 123
                height: 111
                color: "#ff8000"
                MouseArea{
                    id:account_to_menu_button
                    width: parent.width
                    height: parent.height
                }
            }
        }

        Rectangle {
            id: account_rectangle
            x: 574
            y: 41
            width: 138
            height: 131
            color: "#ffffff"
            radius: 10
        }

        RowLayout {
            x: 118
            y: 248

            Label {
                id: device_name
                text: qsTr("Name")
                Layout.preferredHeight: 58
                Layout.preferredWidth: 98
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            TextField {
                id: device_name_field
                Layout.preferredHeight: 58
                Layout.preferredWidth: 450
                horizontalAlignment: Text.AlignHCenter
                readOnly: true
            }
        }

        RowLayout {
            x: 118
            y: 328

            Label {
                id: device_count
                text: qsTr("Device")
                Layout.preferredHeight: 58
                Layout.preferredWidth: 98
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            TextField {
                id: device_count_field
                Layout.preferredHeight: 58
                Layout.preferredWidth: 450
                horizontalAlignment: Text.AlignHCenter
                readOnly: true
            }
        }

        RowLayout {
            x: 118
            y: 416

            Label {
                id: owner_hash
                text: qsTr("Hash")
                Layout.preferredHeight: 58
                Layout.preferredWidth: 98
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            TextField {
                id: owner_hash_field
                Layout.preferredHeight: 58
                Layout.preferredWidth: 450
                horizontalAlignment: Text.AlignHCenter
                readOnly: true
            }
        }
    }

}
