#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H


/*
 * 1. connect_raspberry의 obj을 먼저 선언함
 * 2. qt_json_socket_lib를 통해 QTcpsocket를 사용함
 * 3. 만약 send할것이 있으면 여기에서 send를 함
 * 4. 프로토콜은 raspberry_protocol.h으로 프로토콜 완성
 *
 * */
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "qt_json_socket_lib.h"

/*
 * 1. socket의 타임아웃을 실행하기전 반드시 설정
 * 2. Qt_Json_Socket_Lib의 disconnect_slot()의 시그널을 반드시 slot에 설정함
 *
 *
 * */
class tcp_connection : public QObject
{
    Q_OBJECT
public:
    explicit tcp_connection(QObject *parent = 0);
    ~tcp_connection();

    //connect 영역
    bool connect_raspberry(QString ip, bool adjust = false);
    bool disconnect_raspberry();

    //전송 수신
    bool send_Object(QJsonObject o);
    QJsonObject recv_Object();


    //만약 서버에 의해서 disconnect 시그널이 발생시 connect_close()시그널와 해당 Qt_json_socket_Lib를 close함
public slots:
    void disconnect_from_server();


signals:
    void connect_error(QString);
    void connect_close();

private:
    Qt_Json_Socket_Lib client__;

};

#endif // TCP_CONNECTION_H
