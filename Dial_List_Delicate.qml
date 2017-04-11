import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0

Rectangle{
    property alias tempture_dial: tempture_dial
    property alias setting_tempture: setting_tempture
    property alias current_tempture: current_tempture
    property alias device_name: device_name

    signal change_tempture(int value, string device_name)

    width: 700
    height: 280
    color: "#3F51B5"

    ProgressBar {
        id: current_tempture
        x: 403
        y: 158
        rotation: -90
        value: panel_current_tempture/100

    }

    ProgressBar {
        id: setting_tempture
        x: 108
        y: 158
        rotation: -90
    }

    Dial {
        id: tempture_dial
        x: 259
        y: 61
        width: 184
        height: 200
        onPositionChanged: {
            setting_tempture.value = position
        }

        //온도가 바뀌었을경우 시그널을 전송함
        onValueChanged: {
            change_tempture(value*100, panel_name)
        }
    }

    Label {
        id: device_name
        x: 259
        y: 0
        width: 182
        height: 55
        text: panel_name
        font.pointSize: 30
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
