import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
//import QtQuick.Controls.Styles 1.0
import QtQuick.Controls.Material 2.1

Rectangle_Design_Form {

    property alias login_botton: login_botton
    property alias  error_edit:    error_edit
    property string ip_editor:   login_ip_editor.text

    signal req_acc_dev(string ip);

    Item{

        id: login_main_window


        Button{
            id: login_botton
            x: 102
            y: 479
            width: 322
            height: 76
            text: "LOGIN"
            anchors.horizontalCenterOffset: 187
            anchors.horizontalCenter: parent.horizontalCenter
            checkable: false
            highlighted: true
            onClicked: {
                console.debug(qsTr("=========== login device ==========="))
                console.debug(qsTr("ip:"), login_ip_editor.text)
                req_acc_dev(login_ip_editor.text)
            }


        }

        TextField {
            id: login_title
            x: 169
            y: 8
            width: 357
            height: 186
            text: qsTr("BOILER")
            anchors.horizontalCenterOffset: 187
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            readOnly: true
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
            x: 8
            y: 281
            width: 63
            height: 32
            text: qsTr("IP")
            font.pointSize: 30
            Layout.preferredHeight: 66
            Layout.preferredWidth: 96
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: login_ip_editor
            x: 74
            y: 281
            width: 274
            height: 42
            text: "127.0.0.1"
            Layout.columnSpan: 2
            Layout.preferredHeight: 66
            Layout.preferredWidth: 363

        }

        Label {
            id: error_edit
            objectName: "error_edit"

            x: 115
            y: 334
            width: 356
            height: 40
            anchors.horizontalCenterOffset: 187
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }


    }


}
