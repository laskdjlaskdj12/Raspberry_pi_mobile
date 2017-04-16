#include <QTest>

#include <QObject>

#include <QTcpServer>
#include <QThread>
#include <QHostAddress>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "qt_json_socket_lib.h"

//unit_test_package
#include "ip_login_section.h"
#include "adjust_device_contrler.h"


class Unit_test_Server:public QObject{
    Q_OBJECT
public:

    Unit_test_Server(QObject* parent = 0){

        temp_serv = new QTcpServer;
        lib = new Qt_Json_Socket_Lib;

        connect (temp_serv, SIGNAL(newConnection()), this, SLOT(start_server_recv()));

        lib->set_connect_timeout (3000);
        lib->set_recv_timeout (3000);
        lib->set_send_timeout (3000);

    }


    ~Unit_test_Server(){
        temp_serv->deleteLater ();
        lib->deleteLater ();
    }

signals:
    void disconnect_signal();

public slots:

    void start_Unit_test_server(){

        if (temp_serv->listen (QHostAddress::Any, 43100) == false){
            qDebug()<<"[Error_Unit_test_Server] : This is error of server listening : "<<__LINE__;
        }
    }

    void start_server_recv(){

        try{

            QJsonDocument rcv_doc;
            QJsonObject obj;
            QJsonObject snd_obj;


            lib->set_socket (temp_serv->nextPendingConnection ());

            rcv_doc = lib->recv_Json ();

            qDebug()<<"=================================";
            qDebug()<<(QString)rcv_doc.toJson(QJsonDocument::Indented);
            qDebug()<<"=================================";
            qDebug()<<"\n\n\n\n\n";

            snd_obj["connect"] = true;

            if (lib->send_Json (snd_obj) == false){   throw QString("[Debug] : Error of Sending_Json");}

        }catch(QString& e){
            qDebug()<<"[Error] : "<< e;
        }

    }
private:
    Qt_Json_Socket_Lib* lib;
    QTcpServer*         temp_serv;

};




















class Unit_test:public QObject{
    Q_OBJECT
public:

    //생성자에서는 가상 서버를 먼저 생산을 함
    Unit_test(QObject* parent = 0);
    ~Unit_test();

signals:
    void start_server();
private slots:
    void ip_login_selection();
    void add_device();
    void add_device_duplicate();
    void remove_device();
    void update_device();
    void check_device();
    void set_device_tempture();
    void get_device_tempture();

private:

    Unit_test_Server* serv;
    Ip_Login_Section* ip_login;
    adjust_device_controler* controler;
    QThread thread;

    //QSqlDatabase db;
};

//가상 서버를 먼저 생성
Unit_test::Unit_test(QObject *parent)
{

    serv = new Unit_test_Server;
    controler = new adjust_device_controler;
    ip_login = new Ip_Login_Section;

    serv->moveToThread (&thread);

    //쓰레드 start 시그널 바인딩을 Unit_test_Server를 listen하도록 바인딩 시킴
    connect (&thread, SIGNAL(started()), serv, SLOT(start_Unit_test_server()));

    //쓰레드를 시작함
    thread.start ();


}


Unit_test::~Unit_test()
{
    serv->deleteLater ();
    controler->deleteLater ();
}


void Unit_test::ip_login_selection()
{
    ip_login->set_ip ("127.0.0.1");
    QCOMPARE (ip_login->login_to_device (), 0);
}

void Unit_test::add_device()
{

    QSqlDatabase db;

    //db로드
    if (QSqlDatabase::contains ("Client_device_list")){
        db.database ("Client_device_list");

    } else {

        db = QSqlDatabase::addDatabase ("QSQLITE", "Client_device_list");

        if(db.isValid () != true){
            qDebug()<<"[Error_Debug] : QSQLITE Driver is not loaded";
            return;
        }

        db.setDatabaseName ("Client_device_list.db");
    }

    //db오픈
    if(db.open () == false){
        qDebug()<<"[Error_Debug] : "<<db.lastError ().text ();
    }

    QSqlQuery db_query(db);

    db_query.prepare ("SELECT `device_pid` FROM `Device_list` ");


    //만약 db_query가 fail일경우
    if (db_query.exec () == false){

        QCOMPARE(false,true);
        qDebug()<<"[Error_Debug] : db_qeury is error : "<<db_query.lastError ();
        return;
    }

    db_query.last ();

    //만약 test_row가 있다면
    if (db_query.at () + 1 != 0){
        db.exec ("DELETE FROM `Device_list` WHERE `device_pid` = 0 ");
    }


    controler->set_device_gpio (17);
    controler->set_device_name ("Boiler");
    controler->set_device_type ("Moter");
    QCOMPARE(controler->add_device (), 0);
}

void Unit_test::add_device_duplicate()
{

    controler->set_device_gpio (17);
    controler->set_device_name ("Boiler");
    controler->set_device_type ("Moter");
    QCOMPARE(controler->add_device (), -1);
}

void Unit_test::remove_device()
{

    QSqlDatabase db;

    //db로드
    if (QSqlDatabase::contains ("Client_device_list")){
        db.database ("Client_device_list");

    } else {

        db = QSqlDatabase::addDatabase ("QSQLITE", "Client_device_list");
        db.setDatabaseName ("Client_device_list.db");
    }

    if(db.open () == false){

    }

    QSqlQuery db_query(db);

    db_query.prepare ("SELECT `device_pid` FROM `Device_list` WHERE `device_type` = \"MOTER\"");


    //만약 db_query가 fail일경우
    if (db_query.exec () == false){

        QCOMPARE(false,true);
        qDebug()<<"[Error_Debug] : db_qeury is error : "<<db_query.lastError ();
        return;
    }

    db_query.last ();

    //만약 test_row가 있다면
    if (db_query.at () + 1 != 0){
        qDebug()<<"[Error_Debug] : No SEARCH PID";
        QCOMPARE(false, true);
    }

    db_query.first ();

    QCOMPARE(controler->remove_device ( db_query.value (0).toString ().toInt ()), 0);
}

void Unit_test::update_device()
{

}

void Unit_test::check_device()
{

}

void Unit_test::set_device_tempture()
{

}

void Unit_test::get_device_tempture()
{

}

QTEST_MAIN(Unit_test)
#include "unit_test.moc"
