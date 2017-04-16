#include "tcp_connection.h"

tcp_connection::tcp_connection(QObject *parent) : QObject(parent)
{
    //Qt_Json_socket_lib에 client 소켓을 할당함
    client__.make_QTcpSocket ();

    //client의 disconnect 시그널을 받을 slot를 작성함
    connect(&client__, SIGNAL(disconnect_from_socket()), this,SLOT(disconnect_from_server()));

    client__.set_connect_timeout (3000);
    client__.set_recv_timeout (3000);
    client__.set_send_timeout (3000);
}
tcp_connection::~tcp_connection (){
    client__.disconnect_server ();

}

//만약 connect가 됬을경우 signal을 emit함
bool tcp_connection::connect_raspberry(QString ip, bool adjust)
{
    try{
        QJsonDocument doc;
        QHostAddress addr(ip);


        //서버에 43100 포트로 connect함
        client__.connect_server (addr, 43100);
        qDebug()<<"[Info] : connecting Server";


        //Json 프로토콜 connect 작성
        QJsonObject obj;
        obj["connect"] = true;

        //만약 조작이 true 일경우
        if(adjust == true){
            obj["device"]  = true;
        }



        //프로토콜 송신영역
        qDebug()<<"[Info] : send Connect_Protocol";
        if(client__.send_Json (obj) != true){
            qDebug()<<"[Error] : send_Json is fail";
            throw client__.get_socket ()->error ();
        }


        //프로토콜 수신영역
        qDebug()<<"[Info] : recv Connect_Protocol_reply";
        doc = client__.recv_Json ();
        if(doc.isNull ()){
            qDebug()<<"[Error] : recv JsonProtocol is NULL";
            emit connect_error ("No come JsonDocument");
        }


        //만약 doc.object에서 connect = false가 됬을경우
        if(doc.object ()["connect"].toBool () != true){

            qDebug()<<"[Error] : recv fail connect of Json_Protocol";
            emit connect_error ("Protocol object is fail by connect obj : false");
        }

        //ip연결 완료
        qDebug()<<"[Info]: Connect ip:"<<ip;
        return true;

    }catch(QAbstractSocket::SocketError& e){
        qDebug()<<"[Error] :  Error of connect_raspberry: Error number: "<<client__.get_socket ()->errorString ();
        emit connect_error (client__.get_socket ()->errorString ());
    }
}

bool tcp_connection::disconnect_raspberry()
{
    QJsonObject     obj;

    //disconnect 프로토콜을 완성
    obj["disconnect"] = true;

    //라즈베리파이에 프로토콜을 전송
    client__.send_Json (obj);

    //라즈베리파이에 서버를 disconnect함
    client__.disconnect_server ();


}

bool tcp_connection::send_Object(QJsonObject o)
{
    if(client__.send_Json (o) != true){
        qDebug()<<"[Error] : send Json is fail : "<<client__.get_socket ()->errorString ();
        return false;
    }
    qDebug()<<"[Info] : send Json is clear";
    return true;
}

QJsonObject tcp_connection::recv_Object()
{
    QJsonDocument rcv_doc = client__.recv_Json ();
    if(rcv_doc.isNull ()){
        qDebug()<<"[Error] : recv Json is fail"<<client__.get_socket ()->errorString ();

        return rcv_doc.object ();
    }
    qDebug()<<"[Info] : recv Json is clear";
    return rcv_doc.object ();
}


//### slot 영역

//만약 서버에서 disconnect 시그널이 발생시
void tcp_connection::disconnect_from_server()
{
    qDebug()<<"[Info] : disconnect from server";

    //클라이언트의 disconnect_server를 emit함
    client__.disconnect_server ();
}


