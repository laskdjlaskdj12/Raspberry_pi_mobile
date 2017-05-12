import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQml.Models 2.2

//import QtQuick.Controls.Material 2.1

Rectangle_Design_Form {
    id: main_indicator_panel
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
                             panel_index           : Panel_index,
                             panel_name:             Device_name_String,
                             panel_current_tempture: Device_current_tempture,
                             panel_setting_tempture: Device_setting_tempture,
                             panel_pid             : Device_pid

                         })

        //패널 인덱스 재설정
        var penl_size = dial_list.count;
        for(var i = 0; i < penl_size; i++){

            dial_list.get(i).panel_index = i
        }
    }

    //디바이스 제거시 해당 루틴을 실행함
    function remove_device_panel (Panel_index){

        dial_list.remove(Panel_index)

        //패널 인덱스 재설정
        var penl_size = dial_list.count;
        for(var i = 0; i < penl_size; i++){

            dial_list.get(i).panel_index = i
        }
    }

    //tabbar 캐시 리스트 패널 추가
    function add_server_cache_list_panel (server_ip, is_alive){

        var color;
        if ( is_alive == false){
            color = "Red"
        }
        else {
            color = "Green"
        }

        tab_bar_list_model.append({
                                      panel_ip            : server_ip,
                                      panel_states_color  : color,
                                      panel_index_states  : tab_bar_list_model.count
                                  })

        //해당 인덱스를 찾아서 states 색깔을 바꿈
        var penl_size = tab_bar_list_model.count;
        for(var i = 0; i < penl_size; i++){

            tab_bar_list_model.get(i).panel_index = i;
        }
    }

    //tabbar 에서 서버 상태가 변경됬을경우
    function change_server_states( is_active, ip){

        var color;
        if ( is_active == false){
            color = "Red"
        }
        else {
            color = "Green"
        }

        for(var i = 0; i < tab_bar_list_model.count; i++){
            if ( tab_bar_list_model.get(i).panel_ip == ip){
                tab_bar_list_model.get(i).panel_states_color = color;
            }
        }
    }

    //==================== SIGNAL AREA ====================
    //디바이스 제거시 pid를 메인함수로 전송해서 제거를함
    signal remove_device_pid(string device_pid);
    signal send_device_adjust_tempture(int value, string pid, int index);

    //서버에서 캐시 리스트를 클릭을 했을시 이벤트가 발생되서 해당 서버가 살아있는지를 체크하게하는것
    signal server_cache_list_click_signal(string ip)
    //==================== 디바이스 패널 리스트 뷰 ====================
    //메인컨트롤러는 리스트 형태 그리고 리스트를 누르면 해당 위치별로 등록된 컨트롤러가 나타나서 조절을 가능하게함

    //id: boiler_main_panel
    x: 0
    y: 0
    width: 375
    height: 667
    property alias menu_back_button: menu_back_button
    objectName: "boiler_main_panel"
    //Material.theme: Material.Dark
    //Material.accent: Material.Purple

    Rectangle {
        id: menu_bar
        x: 0
        y: 0
        width: 375
        height: 70
        color: "#34ea9a"
        radius: 4
        //Material.accent: Material.Purple

        Rectangle {
            id: account_rectangle
            x: 259
            y: 8
            width: 108
            height: 113
            color: "#ffffff"
            radius: width* 0.5
            MouseArea{
                id: account_rectangle_button
                x: 0
                y: 0
                width: parent.width
                height: parent.height

                Image {
                    id: person_icon
                    x: 0
                    y: 0
                    width: 108
                    height: 113
                    smooth: false
                    clip: true
                    source: "../icon/person_icon_1.png"
                }
            }
        }

        Rectangle {
            id: side_menu_button
            x: 0
            y: 0
            width: 70
            height: 70
            color: "#34ea9a"
            border.color: "#070606"

            MouseArea{
                id: side_menu_button_area
                x: 0
                y: 0
                width: parent.width
                height: parent.height
            }

            Image {
                id: menu_image1
                x: 19
                y: 19
                width: 32
                height: 32
                source: "../icon/menu_icon_1.png"
            }
        }


    }

    //==================== 디바이스 패널 리스트 뷰 ====================
    ListView {
        id: listView
        objectName: "listView"
        x: 17
        y: 154
        width: 342
        height: 489
        delegate: Dial_List_Delicate{

            signal change_tempture_signal(int value, string device_pid, int panel_index)

            function change_dial_tempture( value,  device_pid,  panel_index){

                console.debug(qsTr("change tempture :"), value, qsTr(" device_pid : "), device_pid, qsTr(" panel_index : "), panel_index);
                send_device_adjust_tempture(value, device_pid, panel_index);
            }

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
                        main_indicator_panel.remove_device_pid( device_pid )
                    }
                }
            }
        }

        interactive: true
        model: dial_list
        clip: true


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
        x: -200
        y: 0
        width: 200
        height: parent.height
        border.color: "#000000"
        //Material.background: Material.Red
        visible: true



        Rectangle {

            id: menu_back_button
            x: 0
            y: 0
            width: 117
            height: 70
            color: "#fbb03b"
            border.width: 1
            border.color: "#090808"

            MouseArea{
                id:menu_back_button_mouse
                x: parent.x
                y: parent.y

                width: parent.width
                height: parent.height
            }

            Image {
                id: menu_image
                x: 24
                y: 0
                width: 68
                height: 70
                source: "../icon/back_icon_1.png"
            }

            Rectangle {
                id: rectangle
                y: 0
                width: 82
                height: 70
                color: "#fbb03b"
                anchors.left: parent.right
                anchors.leftMargin: 0
            }
        }

        //탭바의 리스트뷰
        //접속기록을 리스트 뷰하여 저장함
        ListView{

            id: tab_bar_list_view
            x: 0
            y: 153
            width: 200
            height: 409
            model: tab_bar_list_model
            delegate: Server_cache_list_delicate{}
            clip: true
        }

        Rectangle {
            id: add_tab_button
            x: 8
            y: 109
            width: 184
            height: 38
            color: "#ffffff"
            visible: false

            Text {
                id: text1
                x: 57
                y: 4
                width: 71
                height: 30
                text: qsTr("ADD")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 20
            }
        }

        Rectangle {
            id: remove_tab_remove
            x: 8
            y: 153
            width: 184
            height: 38
            color: "#ffffff"
            visible: false

            Text {
                id: text2
                x: 25
                y: 3
                width: 135
                height: 32
                text: "REMOVE"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 20
            }
        }
    }

    //==================== 디바이스 add ====================
    RowLayout {
        id: rowLayout
        x: 17
        y: 100


        Button {
            id: remove_button
            text: qsTr("")
            z: -6
            smooth: false
            highlighted: true
            onClicked: {
                dial_list.remove(listView.currentIndex)
            }

            Image {
                id: add_button_icon1
                x: 15
                y: 9
                width: 34
                height: 31
                source: "../icon/remove_icon.png"
            }
        }
        Button {
            id: add_button
            text: qsTr("")
            highlighted: true
            enabled: true
            clip: false
            smooth: false
            onClicked: {

                main_indicator_panel.state = "Add_Device_state"

                //디바이스들 추가시 실험할때 사용함
                //add_device(dial_list.count, dial_list.count, 0, 0, "12321")

                //디바이스 탭서버 추가시 사용함
                //add_server_cache_list_panel("127.0.0.1", false);

            }

            Image {
                id: add_button_icon
                x: 15
                y: 9
                source: "../icon/add_icon.png"
                width: 34
                height: 31
            }

        }
    }

    Label {
        id: err_label
        x: 8
        y: 65
        width: 230
        height: 37
        text: qsTr("")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    //==================== 디바이스 패널 리스트 모델 ====================
    Dial_List_Model{
        id: dial_list

    }

    //==================== 디바이스 ADD 페이지 ====================
    Device_Add_Page {
        id: device_Add_Page
        objectName: "device_add_panel_obj"
        x: 375
        y: 0
    }
    //==================== TabBar 의 접속 서버 기록 캐시 ====================
    Server_cache_list_model{
        id: tab_bar_list_model

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
                width: 117
                height: 70
            }

            PropertyChanges {
                target: menu_image1
                x: 19
                y: 19
                width: 32
                height: 32
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
                x: 0
                y: 0
                width: 117
                height: 68
            }

            PropertyChanges {
                target: account_rectangle_button
                width: 138
                height: 131
            }

            PropertyChanges {
                target: rowLayout
                visible: false
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


