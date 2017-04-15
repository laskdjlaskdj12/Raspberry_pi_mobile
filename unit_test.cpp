#include <QTest>
#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "qt_json_socket_lib.h"


//unit_test_package
#include "ip_login_section.h"
#include "adjust_device_contrler.h"


class Unit_test_Server:public QObject{
    Q_OBJECT
public:

    Unit_test_Server(){

        temp_serv = new QTcpServer;
        lib = new Qt_Json_Socket_Lib;

        connect(temp_serv, SIGNAL(newConnection()), this, SLOT(start_server_recv()));

        lib->set_connect_timeout (3000);
        lib->set_recv_timeout (3000);
        lib->set_send_timeout (3000);


    }
    void open_server(){

        if(temp_serv->listen (QHostAddress::Any, 43100) != true){
            qDebug()<<"[Error] : This is error of server listening";
        }
    }

    ~Unit_test_Server(){
        temp_serv->deleteLater ();
        lib->deleteLater ();
    }

public slots:
    void start_server_recv(){

        try{

            QJsonObject obj;
            QJsonObject snd_obj;


            lib->set_socket (temp_serv->nextPendingConnection ());

            obj = lib->recv_Json ();

            QJsonDocument doc;
            doc.setObject (obj);
            qDebug()<<"=================================";
            qDebug()<<(QString)doc.toJson(QJsonDocument::Compact);
            qDebug()<<"=================================";
            qDebug()<<"\n\n\n\n\n";

            snd_obj["connect"] = true;

            if(lib->send_Json (snd_obj) != true){   throw QString("[Debug] : Error of Sending_Json");}

        }catch(QString& e){
            qDebug()<<"[Error] : e";
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

private slots:
    void ip_login_selection();
    void add_device();
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

};

//가상 서버를 먼저 생산
Unit_test::Unit_test(QObject *parent)
{
    serv = new Unit_test_Server;
    controler = new adjust_device_controler;
    ip_login = new Ip_Login_Section;

    serv->moveToThread (&thread);

    QObject::connect(&thread, SIGNAL(started()), serv, SLOT(start_server_recv()));

}

Unit_test::~Unit_test()
{
    serv->deleteLater ();
    controler->deleteLater ();
}


void Unit_test::ip_login_selection()
{
    ip_login->set_ip ("127.0.0.1");
    QCOMPARE(ip_login->login_to_device (),0);
}

void Unit_test::add_device()
{
    controler->set_device_gpio (17);
    controler->set_device_name ("Boiler");
    controler->set_device_type ("Moter");
    controler->add_device ();

}

void Unit_test::remove_device()
{

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
