import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0


//Dial 리스트 모델에서는 panel_의 naming convention이 들어감
//In Dial_List Model have naming convention to panel_.
Rectangle{
    property alias tempture_dial: tempture_dial
    property alias setting_tempture: setting_tempture
    property alias current_tempture: current_tempture
    property alias device_name: device_name
    property string device_pid: panel_pid
    property int    device_panel_index: panel_index

    /*signal change_tempture_signal(int value, string device_pid, int panel_index)

    function change_dial_tempture( value,  device_pid,  panel_index){

        console.debug(qsTr("change tempture :"), value, qsTr(" device_pid : "), device_pid, qsTr(" panel_index : "), panel_index);
        parent.change_tempture_signal(value, device_pid, panel_index);
    }*/

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
            //change_tempture_signal(value*100, panel_pid, panel_index)
            change_dial_tempture(value * 100, panel_pid, panel_index)
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
