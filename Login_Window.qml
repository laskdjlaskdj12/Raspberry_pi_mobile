import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls.Material 2.1

Rectangle_Design_Form {

    property alias login_botton: login_botton
    property alias  error_edit: error_edit
    property string ip_editor:   login_ip_editor.text

    signal req_acc_dev(string ip)

    Item{


        width: 720
        height: 960
        id: login_main_window
        x: 0
        y: 0


        Button{
            id: login_botton
            x: 102
            y: 832
            width: 516
            height: 76
            text: "LOGIN"
            anchors.horizontalCenter: parent.horizontalCenter
            checkable: false
            highlighted: true
            onClicked: {
                console.debug(qsTr("This is not a "))
                req_acc_dev(login_ip_editor.text)
            }


        }

        TextField {
            id: login_title
            x: 169
            y: 21
            width: 383
            height: 186
            text: qsTr("BOILER")
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 50
        }

        GridLayout {
            x: 93
            y: 517
            anchors.horizontalCenterOffset: 26
            anchors.horizontalCenter: parent.horizontalCenter
            rows: 3
            columns: 3
        }

        Label {
            id: id_label
            x: 134
            y: 517
            width: 90
            height: 53
            text: qsTr("IP")
            font.pointSize: 30
            Layout.preferredHeight: 66
            Layout.preferredWidth: 96
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: login_ip_editor
            x: 238
            y: 517
            width: 330
            height: 60
            text: ""
            Layout.columnSpan: 2
            Layout.preferredHeight: 66
            Layout.preferredWidth: 363

        }

        Label {
            id: error_edit
            objectName: "error_edit"

            x: 115
            y: 608
            width: 460
            height: 58
            anchors.horizontalCenterOffset: -15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }


    }


}
