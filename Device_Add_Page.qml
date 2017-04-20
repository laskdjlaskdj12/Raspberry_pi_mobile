import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Universal 2.1
import QtQuick.Layouts 1.0

Rectangle_Design_Form {

    property string add_device_name: device_name_field.text
    property int    add_device_gpio: gpio_field.value
    property string add_device_type: device_type_field.displayText
    property alias  add_button: add_device_button
    property alias  back_button: back_to_menu

    //=================== 시그널 영역 ==========================
    signal add_raspberry_Device(string d_name, int gpio, string d_type)

    RowLayout {
        x: 142
        y: 402

        Label {
            id: type_label
            text: qsTr("Device_Type")
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
            text: qsTr("add_Device_type")
            onActiveFocusChanged: {
                text: qsTr("")
            }
        }
    }

    SpinBox {
        id: gpio_field
        x: 277
        y: 481
        width: 167
        height: 57
    }

    Label {
        id: type_label1
        x: 142
        y: 481
        text: qsTr("GPIO")
        Layout.preferredHeight: 62
        Layout.preferredWidth: 129
        font.pointSize: 20
    }

    Label {
        id: type_label3
        x: 142
        y: 317
        text: qsTr("Name")
        Layout.preferredHeight: 62
        Layout.preferredWidth: 129
        font.pointSize: 20
    }

    TextField {
        id: device_name_field
        x: 277
        y: 317
        width: 341
        height: 62
        text: qsTr("Text Field")
        onActiveFocusChanged: {
            text: qsTr("")
        }
    }

    Button {
        id: add_device_button
        x: 461
        y: 759
        width: 236
        height: 64
        text: qsTr("Add")
        onClicked: {
            console.log("[Info] : add_device_to_raspberry : ",add_device_name," : ",add_device_gpio," : ",add_device_type)
            add_raspberry_Devcie(add_device_name, add_device_gpio, add_device_type)
            gpio_field.value = 0
            device_name_field.text = qsTr("")
            device_type_field.text = qsTr("")
        }
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 186
        height: 109
        color: "#ff8000"

        MouseArea{
            id: back_to_menu
            width: parent.width
            height: parent.height
        }
    }

}
