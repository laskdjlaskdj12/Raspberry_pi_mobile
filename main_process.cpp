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

   //tempture가 바귀었을때
   QObject::connect (add_device_obj, SIGNAL(add_raspberry_Device(QString, int, QString)), this, SLOT(add_raspberry_device(QString,int,QString)));

   //tempture를 요청시
   QObject::connect ()
}

void Main_Process::set_root_qml_object(QObject *obj)
{
    root_obj = obj;
}

QObject *Main_Process::get_root_qml_object()
{
    return root_obj;
}







// ####################################### slot area #######################################
void Main_Process::check_ip_connect(QString ip)
{

}

void Main_Process::add_raspberry_device(QString name, int gpio, QString d_type)
{

}

void Main_Process::set_device_tempture(int value, QString pid)
{

}
