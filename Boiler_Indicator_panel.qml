import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQml.Models 2.2
import QtQuick.Controls.Material 2.1

Rectangle_Design_Form {
    id: main_indicator_panel
    width: 720
    height: 960
    state: "Main_state"

    property alias account_button: account_rectangle_button
    property alias sidemenu_to_menu: menu_back_button
    property alias side_menu: side_menu
    property string err_tag : err_label.text
    property int  panel_count: dial_list.count

    //==================== JAVASCRIPT ====================

    //device_add_page로 가기 디바이스 추가 버튼을 눌렀을시
    function add_device_button_click (){
        main_indicator_panel.state = "Add_Device_state"
    }

    //device_add_page에서 뒤로가기
    function add_device_button_click_done (){
        main_indicator_panel.state = "Main_state"
    }

    //다비이스 에 디바이스에서 설정이 완료된 tempture값을 설정함
    function change_device_tempture (index, tempture){
        dial_list.get(index).panel_current_tempture = tempture;
    }

    //해당 함수는 c++에서 디바이스를 추가할때 사용함
    function add_device(Panel_index, Device_name_String, Device_current_tempture, Device_setting_tempture, Device_pid){

        dial_list.append({
                             panel_name:             Device_name_String,
                             panel_current_tempture: Device_current_tempture,
                             panel_setting_tempture: Device_setting_tempture,
                             panel_pid             : Device_pid,
                             panel_index           : Panel_index
                         })

        //현재 패널창안에 있는 디바이스패널들의 인덱스를 전부 재설정
        var penl_size = dial_list.count
        for(var i = 0; i < penl_size; i++){

            dial_list.get(i).panel_index = i
        }
    }

    //디바이스 제거시 해당 루틴을 실행함
    function remove_device_panel (Panel_index){

        dial_list.remove(Panel_index)

        //현재 패널창안에 있는 디바이스패널들의 인덱스를 전부 재설정
        var penl_size = dial_list.count
        for(var i = 0; i < penl_size; i++){

            dial_list.get(i).panel_index = i
        }
    }

    //==================== SIGNAL AREA ====================
    //디바이스 제거시 pid를 메인함수로 전송해서 제거를함
    signal remove_device_pid(string device_pid)

    //==================== 디바이스 패널 리스트 뷰 ====================
    //메인컨트롤러는 리스트 형태 그리고 리스트를 누르면 해당 위치별로 등록된 컨트롤러가 나타나서 조절을 가능하게함
    Item{
        id: boiler_main_panel
        objectName: "boiler_main_panel"
        width: parent.width
        height: parent.height
        Material.theme: Material.Dark
        Material.accent: Material.Purple

        Rectangle {
            id: menu_bar
            x: 0
            y: 0
            width: 720
            height: 111
            color: "#ffffff"
            radius: 4
            Material.accent: Material.Purple

            Rectangle {
                id: account_rectangle
                x: 574
                y: 41
                width: 138
                height: 131
                color: "#ffffff"
                radius: 10
                MouseArea{
                    id: account_rectangle_button
                    width: 138
                    height: 131
                }
            }

            Rectangle {
                id: side_menu_button
                x: 0
                y: 2
                width: 158
                height: 109
                color: "Orange"
                MouseArea{
                    id: side_menu_button_area
                    width: parent.width
                    height: parent.height
                }
            }


        }

        //==================== 디바이스 패널 리스트 뷰 ====================
        ListView {
            id: listView
            objectName: "listView"
            x: 8
            y: 178
            width: 700
            height: 700
            delegate: Dial_List_Delicate{
                id: dial_delegate
                objectName: "dial_delegate"
                //==================== 디바이스 패널 remove ====================
                Rectangle {
                    id: remove_panel
                    x: 583
                    y: 60
                    width: 109
                    height: 27
                    color: "#ff8000"

                    MouseArea{

                        id: remove_panel_button
                        width: parent.width
                        height: parent.height
                        onClicked: {

                            console.debug(qsTr("Remove index : "), panel_index)
                            remove_device_panel( panel_index )
                            remove_device_pid( device_pid )
                        }
                    }
                }
            }

            model: dial_list


            //리스트 뷰의 하이라이트
            highlight: Rectangle{
                width: parent.width
                color: "lightgray"

            }

        }


        //==================== 사이드 바 menu ====================
        //사이드 메뉴로는 컴포넌트 자동 업데이트나 아니면 로그인 상태 등등을 표시함

        Rectangle{
            id: side_menu
            x: -246
            y: 0
            width: parent.width/3
            height: parent.height
            Material.background: Material.Red
            visible: true

            Rectangle {
                id: menu_back_button
                y: 0
                anchors.left: parent.left
                anchors.right: parent.right
                width: 200
                height: 200
                color: "Orange"
                opacity: 0
                MouseArea{
                    id:menu_back_button_mouse
                    x: parent.x
                    y: parent.y

                    width: parent.width
                    height: parent.height
                }
            }

        }

        //==================== 디바이스 add ====================
        RowLayout {
            x: 273
            y: 124

            Button {
                id: add_button
                text: qsTr("Add")
                onClicked: {

                    //main_indicator_panel.state = "Add_Device_state"

                    add_device(dial_list.count, dial_list.count, 0, 0, "12321")

                }

            }

            Button {
                id: remove_button
                text: qsTr("Remove")
                onClicked: {
                    dial_list.remove(listView.currentIndex)
                }
            }
        }

        Label {
            id: err_label
            x: 23
            y: 130
            width: 230
            height: 37
            text: qsTr("")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
    //==================== 디바이스 패널 리스트 모델 ====================
    Dial_List_Model{
        id: dial_list

    }

    //==================== 디바이스 ADD 페이지 ====================
    Device_Add_Page {
        id: device_Add_Page
        x: 720
        y: 0
    }

    //==================== 페이지 state ====================

    states: [
        State {
            name: "Main_state"

            PropertyChanges {
                target: side_menu
                x: - side_menu.width
                y: 0
                visible: true
            }

            PropertyChanges {
                target: menu_back_button
                width: 240
                height: 111
            }

        },

        State {
            name: "Side_Menu_state"

            PropertyChanges {
                target: side_menu
                x: 0
                y: 0
                visible: true
            }

            PropertyChanges {
                target: menu_back_button
                width: 240
                height: 111
            }

            PropertyChanges {
                target: account_rectangle_button
                width: 138
                height: 131
            }
        },

        State {
            name: "Add_Device_state"

            PropertyChanges {
                target: device_Add_Page
                x: 0
                y: 0
            }
        }


    ]

    //==================== 페이지 transistions ====================
    transitions: [

        Transition {
            from: "Main_state"
            to: "Side_Menu_state"


            NumberAnimation {
                target: side_menu
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }
        },

        Transition {
            from: "Side_Menu_state"
            to: "Main_state"

            NumberAnimation {
                target: side_menu
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }

        },
        Transition {
            from: "Main_state"
            to: "Add_Device_state"

            NumberAnimation {
                target: device_Add_Page
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }

        },

        Transition {
            from: "Add_Device_state"
            to: "Main_state"

            NumberAnimation {
                target: device_Add_Page
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }

        }
    ]

    Connections{
        target: side_menu_button_area
        onClicked: {
            main_indicator_panel.state = "Side_Menu_state"
        }
    }

    Connections{
        target: menu_back_button_mouse
        onClicked:{
            main_indicator_panel.state = "Main_state"
        }
    }

    Connections{
        target: device_Add_Page.back_button
        onClicked:{
            main_indicator_panel.state = "Main_state"
        }
    }

    Connections{
        target: device_Add_Page.add_button
        onClicked:{
            main_indicator_panel.state = "Main_state"
        }
    }

}


