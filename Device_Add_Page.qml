import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.1

Rectangle_Design_Form {

    property string add_device_name: device_name_field.text
    property int    add_device_gpio: gpio_field.value
    property string add_device_type: device_type_field.displayText
    property string device_states_label: states_label.text
    property alias  add_button: add_device_button
    property alias  back_button: back_to_menu

    //=================== 시그널 영역 ==========================
    signal add_raspberry_Device(string d_name, int gpio, string d_type)

    RowLayout {
        x: 23
        y: 212

        Label {
            id: type_label
            text: qsTr("Device_Type")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.preferredHeight: 62
            Layout.preferredWidth: 129
            font.pointSize: 20
        }

        TextField {
            id: device_type_field
            x: 277
            y: 317
            width: 341
            height: 62
            text: qsTr("Moter")
            onActiveFocusChanged: {
                text: qsTr("")
            }
        }
    }

    Button {
        id: add_device_button
        x: 63
        y: 531
        width: 236
        height: 64
        text: qsTr("Add")
        onClicked: {
            console.log("[Info] : add_device_to_raspberry : ",add_device_name," : ",add_device_gpio," : ",add_device_type)
            add_raspberry_Device(add_device_name, add_device_gpio, add_device_type)
            gpio_field.value = 0
            device_name_field.text = qsTr("")
            device_type_field.text = qsTr("")
        }
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 112
        height: 62
        color: "#ff8000"

        MouseArea{
            id: back_to_menu
            x: 0
            y: 0
            width: parent.width
            height: parent.height
        }
    }

    Label {
        id: states_label
        x: 30
        y: 389
        width: 301
        height: 46
        text: qsTr("")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    GridLayout {
        x: 23
        y: 157
        rows: 1
        columns: 2

        Label {
            id: type_label3
            text: qsTr("Name")
            Layout.preferredHeight: 29
            Layout.preferredWidth: 60
            font.pointSize: 20
        }

        TextField {
            id: device_name_field
            text: qsTr("Test_Moter")
            Layout.preferredHeight: 43
            Layout.preferredWidth: 219
            onActiveFocusChanged: {
                text: qsTr("")
            }
        }
    }

    GridLayout {
    }

    RowLayout {
        x: 30
        y: 297

        Label {
            id: type_label1
            text: qsTr("GPIO")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.preferredHeight: 62
            Layout.preferredWidth: 129
            font.pointSize: 20
        }

        SpinBox {
            id: gpio_field
            Layout.preferredHeight: 57
            Layout.preferredWidth: 167
        }
    }

}
