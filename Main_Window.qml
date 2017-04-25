import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.1

Item {

    //==================== JAVASCRIPT ====================
    function login_fail(login_fail_reason){
        main_window.state = "Login_Page"
        login_window.error_eidt.text = login_fail_reason
    }

    //로그인에 성공했을경우
    function login_success(){
        main_window.state = "Main_Panel_Page"
    }


    id: main_window
    width: 720
    height: 960

    state: "Login_Page"

    Login_Window{
        id: login_window
        objectName: "login_window_obj"
        x: 0
        y: 0
        width: 720
        height: 960
        Material.theme: Material.Dark
        Material.accent: Material.Pink
    }
    Loding_Screen{
        id: loading_screen
        objectName: "login_screen_obj"
    }

    Account_menu_panel{
        id: account_penl
        objectName: "account_penl_obj"
    }

    Boiler_Indicator_panel{
        id: main_indicator_panel
        visible: true
        objectName: "main_indicator_panel_obj"
    }
    Device_Add_Page{
        id: device_add_panel
        objectName: "device_add_panel_obj"
    }

    states: [
        State {
            name: "Login_Page"

            PropertyChanges {
                target: loading_screen
                x: main_window.width
                y: 0
            }

            PropertyChanges{
                target: main_indicator_panel
                visible: false
            }

            PropertyChanges {
                target: account_penl
                x: main_window.width
                y: 0
            }

            PropertyChanges {
                target: device_add_panel
                x: main_window.width
                y: 0
            }
        },
        State {
            name: "Login_Loading_Page"

            PropertyChanges {
                target: loading_screen
                x: 0
                y: 0
            }

            PropertyChanges{
                target: main_indicator_panel
                visible: false
                x: main_window.width
                y: 0
            }

            PropertyChanges {
                target: account_penl
                x: main_window.width
                y: 0
            }

            PropertyChanges {
                target: device_add_panel
                x: main_window.width
                y: 0
            }

        },
        State {
            name: "Main_Panel_Page"

            PropertyChanges {
                target: loading_screen
                x: main_window.width
                y: 0
            }

            PropertyChanges{
                target: main_indicator_panel
                x: 0
                y: 0
            }

            PropertyChanges {
                target: account_penl
                x: main_window.width
                y: 0
            }

            PropertyChanges {
                target: device_add_panel
                x: main_window.width
                y: 0
            }
        },
        State {
            name: "Boiler_Add_Page"
            PropertyChanges {
                target: loading_screen
                x: main_window.width
                y: 0
            }

            PropertyChanges{
                target: main_indicator_panel
                x: main_window.width
                y: 0
            }

            PropertyChanges {
                target: account_penl
                x: main_window.width
                y: 0
            }

            PropertyChanges {
                target: device_add_panel
                x: 0
                y: 0
            }
        },

        State {
            name: "Account_Page"

            PropertyChanges {
                target: loading_screen
                x: main_window.width
                y: 0
            }

            PropertyChanges{
                target: main_indicator_panel
                x: main_window.width
                y: 0
            }

            PropertyChanges {
                target: account_penl
                x: 0
                y: 0
            }

            PropertyChanges {
                target: device_add_panel
                x: main_window.width
                y: 0
            }
            PropertyChanges {
                target: main_indicator_panel.side_menu
                visible: false

            }
        }
    ]

 transitions: [

        //this is Login_Page to Login_Loading_Page
        Transition {
            from: "Login_Page"
            to: "Login_Loading_Page"


            NumberAnimation {
                target: loading_screen
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }
        },
        Transition {
            from: "Login_Loading_Page"
            to: "Login_Page"


            NumberAnimation {
                target: loading_screen
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }
        },



        //This is Loading_Page to Main_Page_Panel
        Transition {
            from: "Login_Loading_Page"
            to: "Main_Panel_Page"


            NumberAnimation {
                target: login_window
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }
        },Transition {
            from: "Main_Panel_Page"
            to: "Login_Loading_Page"


            NumberAnimation {
                target: login_window
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }
        },


        //this is Main_Panel_Page to Add_Device_Page
        Transition {
            from: "Main_Panel_Page"
            to: "Boiler_Add_Page"


            NumberAnimation {
                target: device_add_panel
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }
        },Transition {
            from: "Boiler_Add_Page"
            to: "Main_Panel_Page"


            NumberAnimation {
                target: device_add_panel
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }
        },


        //this is MainPanel_Page to Account_penl page
        Transition {
            from: "Main_Panel_Page"
            to: "Account_Page"


            NumberAnimation {
                target: account_penl
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }
        },Transition {
            from: "Account_Page"
            to: "Main_Panel_Page"


            NumberAnimation {
                target: account_penl
                property: "x"
                duration: 200
                easing.type: Easing.OutQuad
            }
        }
    ]



/*    Connections{
        target: login_window.login_botton
        onClicked: main_window.state = "Login_Loading_Page"
    } Connections{
        target: loading_screen.loading_next_button
        onClicked: main_window.state = "Main_Panel_Page"
    }Connections{
        target: main_indicator_panel.account_button
        onClicked: main_window.state = "Account_Page"
    } Connections{
        target: account_penl.to_menu_back_button
        onClicked: main_window.state = "Main_Panel_Page"
    }*/
}


