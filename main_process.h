#ifndef MAIN_PROCESS_H
#define MAIN_PROCESS_H

#include <QObject>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QVariant>
#include <QDebug>

#include "ip_login_section.h"
#include "adjust_device_contrler.h"


//메인 윈도우
class Main_Process: public QObject{
public:
    Q_OBJECT

    Main_Process(QObject* parent = 0);
    ~Main_Process();

    int init_main_object();

    int init_signal();

    void set_root_qml_object(QObject* obj);

    QObject* get_root_qml_object();


public slots:

    //로그인 패널에서 ip로그인 버튼이 emit 시그널을 connect함
    void check_ip_connect(QString ip);

    //디바이스를 추가시 slot
    void add_raspberry_device(QString name, int gpio, QString d_type);

    //디바이스 제거시 slot
    void set_device_tempture (int value, QString pid);

private:

    //qml루트 오브젝트를 가지고옴
    QObject* root_obj;

    //main_window qml를 불러옴
    QObject* main_window_obj;

    //로그인 윈도우 오브젝트
    QObject* login_window_obj;

    //로딩 스크린 오브젝트
    QObject* loading_screen_obj;

    //어카운트패널 오브젝트
    QObject* account_panel_info_obj;

    //메인패널 오브젝트
    QObject* main_indicator_panel_obj;

    //디바이스 추가 오브젝트
    QObject* add_device_obj;

    //ip 로그인 세션 오브젝트
    Ip_Login_Section* ip_login;

    //디바이스 컨트롤러 세션
    adjust_device_controler* controler;

};

#endif // MAIN_PROCESS_H
