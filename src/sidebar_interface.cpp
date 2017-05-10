#include "sidebar_interface.h"

Sidebar_interface::Sidebar_interface(QObject *parent) : QObject(parent), __connect_raspberry(false)
{
    //tcp_connection의 클래스에 만약 error가 emit될경우
    connect(&__tcp, SIGNAL(connect_error(QString)), this, SLOT(connect_error_from_server(QString)));
    connect(&__tcp, SIGNAL(connect_close()), this, SLOT(disconnect_from_server()));


}

Sidebar_interface::~Sidebar_interface(){

    //만약 라즈베리파이가 == true일 경우 disconnect_server로 disconnect함
    if(__connect_raspberry == true){
        __tcp.disconnect_from_server ();
    }
}

int Sidebar_interface::get_livingroom_tempture()
{

}

int Sidebar_interface::get_Bathroom_tempture()
{

}

void Sidebar_interface::set_Console_log_Object(QObject *obj)
{

}

void Sidebar_interface::get_headline()
{

}

void Sidebar_interface::get_date()
{

}

void Sidebar_interface::get_weekend()
{

}

void Sidebar_interface::get_time()
{

}

void Sidebar_interface::get_message()
{

}

void Sidebar_interface::get_weather()
{

}







//================= slot 영역 =====================

void Sidebar_interface::set_Bathroom_tempture(int temp)
{
    //먼저 라즈베리파이에 connect 함
    __tcp.connect_raspberry(__Rasp_ip, true);
    qDebug()<<"[Info]: connect in c++ by qml : bathroom_temp:"<<temp;

    QJsonObject obj;;
    obj["tempture"] = temp;
    obj["device"]   = "Bathroom";

    //오브젝트 전송
    if(__tcp.send_Object (obj) != true){
        qDebug()<<"[Error] : Send_Object is fail";
        return;
    }

    //오브젝트 수신
    QJsonObject rcv_obj = __tcp.recv_Object ();


    if(rcv_obj["clear"] != true){
        qDebug()<<"[Info] : setting bathroom_temptrue is fail";
        return;
    }


    qDebug()<<"[Info] : setting bathroom_tempture is clear";

    //서버에 disconnect함
    disconnect_from_server ();

    return;



}

void Sidebar_interface::set_livingroom_tempture(int temp)
{
    __tcp.connect_raspberry (__Rasp_ip, true);

    qDebug()<<"[Info]: connect in c++ by qml : livingroom_temp:"<<temp;

    QJsonObject obj;
    obj["tempture"] = temp;
    obj["device"]   = "Livingroom";


    //오브젝트 전송
    if(__tcp.send_Object (obj) != true){
        qDebug()<<"[Error] : Send_Object is fail";
        return;
    }

    //오브젝트 수신
    QJsonObject rcv_obj = __tcp.recv_Object ();

    if(rcv_obj["clear"] != true){
        qDebug()<<"[Info] : setting bathroom_temptrue is fail";
        return;
    }

    qDebug()<<"[Info] : setting bathroom_tempture is clear";

    disconnect_from_server ();
    return;


}

void Sidebar_interface::ip_send_signal(QString ip)
{
    qDebug()<<"[Info]: Connect in c++ by qml : ip:"<<ip;

    if(Access_Raspberry (ip) != true){
        qDebug()<<"[Error] : Connect raspberry_pi is fail";
        return;
    }
    qDebug()<<"[Info] : Connect raspberry pi is clear";
    return;
}


//####### slot 영역 ##########
void Sidebar_interface::connect_error_from_server(QString err_msg )
{
    qDebug()<<"[Error] : err_msg : "<<err_msg;
}

void Sidebar_interface::disconnect_from_server()
{
    //만약 서버에서 disconnect가 됬을경우 다시 재 connect를 연결함
    qDebug()<<"[Info] : disconnect from Server";

    //서버를 disconnect함
    __tcp.disconnect_raspberry ();

}


//=============== private 영역 ======================

bool Sidebar_interface::Access_Raspberry(QString ip)
{

    //__Rasp_ip에 ip저장
    __Rasp_ip = ip;

    //라즈베리파이 ip연결
    if(__tcp.connect_raspberry (ip) != true){
        qDebug()<<"[Error] : Error of connecting ip";
        return false;
    }

    //라즈베리파이의 접속성공을 알림
    qDebug()<<"[Info] : Raspberry_pi has been connected";
    __connect_raspberry = true;
    return true;
}

//라즈베리파이 접속종료
bool Sidebar_interface::Disconnect_Raspberry()
{
    qDebug()<<"[Info] : disconnect from server";
   __tcp.disconnect_from_server ();
   __connect_raspberry = false;
   return true;
}

