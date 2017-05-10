#ifndef SIDEBAR_INTERFACE_H
#define SIDEBAR_INTERFACE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "tcp_connection.h"



/*
 *
 *
 *
 * */

class Sidebar_interface : public QObject
{
    Q_OBJECT
public:
    explicit Sidebar_interface(QObject *parent = 0);
    ~Sidebar_interface();

    int get_livingroom_tempture();
    int get_Bathroom_tempture();
    void set_Console_log_Object(QObject* obj);


    void get_headline();            //헤드라인 출력
    void get_date();                //날짜 출력
    void get_weekend();             //요일 출력
    void get_time();                //시간 출력
    void get_message();             //수신된 문자메세지를 출력
    void get_weather();             //날씨 출력

public slots:
    void set_Bathroom_tempture(int temp);       //샤워실 온도
    void set_livingroom_tempture(int temp);     //거실 온도
    void ip_send_signal(QString ip);            //ip connection slot

    //라즈베리파이 접속 컨넥션 슬롯
public slots:
    void connect_error_from_server(QString);    //서버에 에러가 발생이될때
    void disconnect_from_server();              //서버에서 disconnect가 발생이 됬을때

    //라즈베리파이 접속컨넥션
private:
    bool Access_Raspberry(QString ip);           //라즈베리파이 접속
    bool Disconnect_Raspberry();                 //라즈베리파이 접속해제

private:
    QSqlDatabase __db;
    QSqlQuery __db_query;                         //db쿼리 전송
    QString __Rasp_ip;                            //라즈베리파이 ip
    QThread __send_thread;                        //라즈베리파이 전송 스레드
    tcp_connection __tcp;                        //tcp 연결 오브젝트
    QObject* __console_log_ouput;                 //콘솔 로그의 output


private:
        int __Bath_temp;                          //샤워실 온도
        int __Room_temp;                          //방안 온도
        bool __connect_raspberry;                 //라즈베리파이 연결확인
};

#endif // SIDEBAR_INTERFACE_H
