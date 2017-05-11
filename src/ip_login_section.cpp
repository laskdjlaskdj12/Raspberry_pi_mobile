#include "ip_login_section.h"

Ip_Login_Section::Ip_Login_Section(QObject *parent) : QObject(parent)
{
    lib = new Qt_Json_Socket_Lib;
    lib->make_QTcpSocket ();
    lib->set_recv_timeout (3000);
    lib->set_send_timeout (3000);
    lib->set_connect_timeout (3000);

    load_server_cache ();
}

Ip_Login_Section::~Ip_Login_Section()
{
    if (lib->get_socket ()->isOpen ()){  lib->get_socket ()->close ();}

    lib->deleteLater ();

}

QString Ip_Login_Section::get_ip(){    return ip_;}

QString Ip_Login_Section::get_last_ip(){

    if (ip_cache_list.isEmpty ()){  return QString("127.0.0.1");}
    else return ip_cache_list.last ();
}

QList<QString> Ip_Login_Section::get_ip_cache_list(){   return ip_cache_list;}

void Ip_Login_Section::set_ip(QString ip){  ip_ = ip;}

int Ip_Login_Section::login_to_device()
{
    try{

        QJsonDocument _doc_;
        QHostAddress addr(ip_);

        lib->connect_server (addr,43100);

        if ( lib->send_Json (send_connect_Json_Synctes ()) == false){    throw Boiler_Controler_Exception(lib->get_socket ()->errorString (), __LINE__);}

        _doc_ = lib->recv_Json ();

        if (_doc_.isNull () || _doc_.isEmpty ()){    throw Boiler_Controler_Exception(QString("Recv_Json document fail"), __LINE__);}

        else if (_doc_.object ()["connect"].toBool () == true){      return 0;}

        else{   throw Boiler_Controler_Exception(QString("Error of recv"), __LINE__); }

        lib->disconnect_server ();

        ip_cache_list.append (ip_);

        //캐시 ip를 저장함
        save_server_cache ();
        return 0;

    }catch(Boiler_Controler_Exception& e){

        e.get_error ();
        return -1;
    }
}



//QJsonObject
QJsonObject Ip_Login_Section::send_connect_Json_Synctes()
{
    QJsonObject _obj_;

    _obj_["connect"] = true;

    return _obj_;
}

void Ip_Login_Section::save_server_cache()
{
    QFile jsonFile("server_cache_list.txt");
    jsonFile.open (QFile::ReadWrite);
    QJsonObject save_obj;

    QList<QString>::iterator it = ip_cache_list.begin ();

    for(uint i = 0; i < ip_cache_list.count (); i++){
        save_obj[i] = it[i];
    }

    jsonFile.write(QJsonDocument(save_obj).toJson ());
}

void Ip_Login_Section::load_server_cache()
{
    //캐시 리스트 불러오기
    QFile jsonFile("server_cache_list.txt");
    jsonFile.open (QFile::ReadWrite);
    QJsonDocument temp_json_doc = fromJson (jsonFile.readAll ());

    if (temp_json_doc.object ().count () != 0 || ! temp_json_doc.isNull ()){

        //캐시 insert
        for(int i = 0; i < temp_json_doc.object ().count () ; i++){
            ip_cache_list.append (temp_json_doc.object ()[i].toString ());
        }
    }
}

void Ip_Login_Section::check_ip_connect(QString ip)
{
    this->set_ip (ip);
    if (this->login_to_device () == 1){

        is_connect = true;
    }

    else{

        is_connect = false;
    }


}

//디바이스 타임아웃시 패널에 전송을 함
void Ip_Login_Section::timeout_to_device()
{
    emit send_timeout ();
}


