#ifndef MAIN_PROCESS_H
#define MAIN_PROCESS_H

#include <QObject>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QVariant>
#include <QDebug>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QSqlDatabase>
#include <QSqlQuery>

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
    void ip_connect_to_raspberry(QString ip);

    //디바이스를 추가시 slot
    void add_raspberry_device(QString name, int gpio, QString d_type);

    //디바이스 제거 slot
    void remove_raspberry_device(QString pid);

    //디바이스 제거시 slot
    void set_device_tempture (int value, QString pid, int index);

private:
    /*//디바이스를 추가함
    int add_device(int Panel_index,
                   QString Device_name,
                   int Device_current_tempture,
                   int Device_setting_tempture,
                   QString Device_pid);

    //디바이스를 제거함
    int remove_device(int Panel_index);

    //디바이스를 수정함
    int */

private:

    //========================== qml Object Area ==========================

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

    //디바이스 메인 패널 의 메인 메뉴
    QObject* panel_menu_obj;

    //디바이스 리스트 뷰 오브젝트
    QObject* list_view_delegate_obj;

    //디바이스 리스트 델리게이트 오브젝트
    QObject* dial_delegate_obj;

    //디바이스 리스트
    QList<QObject*> dev_list;

    //========================== 클라이언트 제어 Area ==========================

    //ip 로그인 세션 오브젝트
    Ip_Login_Section* ip_login;

    //디바이스 컨트롤러 세션
    adjust_device_controler* controler;

    //디바이스 저장할 db
    QSqlDatabase db_;


};

#endif // MAIN_PROCESS_H
