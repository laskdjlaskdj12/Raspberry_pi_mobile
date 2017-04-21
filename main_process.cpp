#include "main_process.h"

Main_Process::Main_Process(QObject *parent) : QObject(parent),\
    root_obj(nullptr),\
    main_window_obj(nullptr),\
    login_window_obj(nullptr),\
    loading_screen_obj(nullptr),\
    account_panel_info_obj(nullptr),\
    main_indicator_panel_obj(nullptr),\
    add_device_obj(nullptr)
{
    ip_login = new Ip_Login_Section;

    controler  = new adjust_device_controler;
}
Main_Process::~Main_Process(){

    ip_login->deleteLater ();
    controler->deleteLater ();
    root_obj->deleteLater ();
    main_window_obj->deleteLater ();
    login_window_obj->deleteLater ();
    loading_screen_obj->deleteLater ();
    account_panel_info_obj->deleteLater ();
    main_indicator_panel_obj->deleteLater ();
    add_device_obj->deleteLater ();

}

int Main_Process::init_main_object ()
{
    try{

        if(root_obj == nullptr){

            throw QString("root_obj property is not setting");
        }

        main_window_obj = root_obj->findChild<QObject*>("main_window_obj");

        login_window_obj = main_window_obj->findChild<QObject*>("login_window_obj");

        loading_screen_obj = main_window_obj->findChild<QObject*>("loading_screen_obj");

        account_panel_info_obj = main_window_obj->findChild<QObject*>("account_penl_obj");

        main_indicator_panel_obj = main_window_obj->findChild<QObject*>("main_indicator_panel_obj");

        add_device_obj = main_window_obj->findChild<QObject*>("device_add_panel_obj");


        return 0;
    }
    catch(QString& e){

        qDebug()<<"[Error] : "<<e;
        return -1;
    }
}

//qml에서 emit된 시그널들을 현재 클래스의 slot으로 connect시킴
int Main_Process::init_signal()
{
    //LoginWindow를 connect시킴
   QObject::connect (login_window_obj, SIGNAL(req_acc_dev(QString)), this, SLOT(check_ip_connect(QString)));

   //Device_add_obj를 connect시킴
   QObject::connect (add_device_obj, SIGNAL(add_raspberry_Device(QString, int, QString)), this, SLOT(add_raspberry_device(QString,int,QString)));

   //Boiler_Indicator_panel ( main_indicator_panel_obj ) 에서 디바이스 제거시
   QObject::connect (main_indicator_panel_obj, SIGNAL(remove_device_pid(QString)), this, SLOT(remove_raspberry_device (QString)));

   //tempture가 바귀었을때
   QObject::connect (add_device_obj, SIGNAL(add_raspberry_Device(QString, int, QString)), this, SLOT(add_raspberry_device(QString,int,QString)));

}

void Main_Process::set_root_qml_object(QObject *obj)
{
    root_obj = obj;
}

QObject *Main_Process::get_root_qml_object()
{
    return root_obj;
}







// ========================== slot Area ==========================
void Main_Process::ip_connect_to_raspberry(QString ip)
{
    /*
     * 1. states를 loading_screen으로 변경
     * 2. Ip_Login_Section으로 ip 로그인 요청
     * 3. 만약 IP_Login_Section이 fail일경우 Login_page로 변경후 에러메세지를 출력함
     * 4. 로그인이 성공적일경우 Login_Loading_Page 에서 Main_Panel_Page로 변경함
     * 5. 디바이스 목록들을 불러서 로딩
     * 6. 만약 디바이스 목록 리턴값이 fail일 경우 Login_page로 변경후 에러메세지를 출력함
     * 7. JsonObject로 리턴시 Device_List에 저장
     * 8. Device_List 에서 모든 디바이스들을 객체 생성하여 저장
     * */

    //states 를 loadingscreen으로 변경
    main_window_obj -> setProperty ("state", "Login_Loading_Page");

    //받은 ip으로 ip를 요청함
    ip_login->set_ip (ip);
    if(ip_login->login_to_device () < 0){


        main_window_obj -> setProperty ("state", "Login_Page");

        //만약 ip의 접속이 fail일 경우 login_page로 변경후 에러메세지를 출력함
        login_window_obj->findChild<QObject*> ("error_edit")->setProperty ("text", "Error of connect of raspberry");

        return;
    }

    //ip연결이 성공시 main_indicator로 state를 변경함
    main_window_obj -> setProperty ("state", "main_indicator_panel_obj");

    //디바이스 목록을 로딩
    QJsonObject device_list = controler -> load_device_list ();

    //만약 디바이스 목록리턴값이 fail일경우 Login_Loading_Page 으로 변경후 에러메세지를 출력함
    if(device_list["Error"].isNull () == false){

        main_window_obj -> setProperty ("state", "Login_Page");

        login_window_obj->findChild<QObject*> ("error_edit")->setProperty ("text", "Error of Receiving Device Data From Server");
    }

}

void Main_Process::add_raspberry_device(QString name, int gpio, QString d_type)
{

}

void Main_Process::remove_raspberry_device(QString pid)
{

}

void Main_Process::set_device_tempture(int value, QString pid)
{

}
