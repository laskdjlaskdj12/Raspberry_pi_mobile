#ifndef IP_LOGIN_SECTION_H
#define IP_LOGIN_SECTION_H

#include <QObject>
#include <qt_json_socket_lib.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QHostAddress>
#include "boiler_controler_exception.h"

class Ip_Login_Section : public QObject
{
    Q_OBJECT
public:
    explicit Ip_Login_Section(QObject *parent = 0);
    ~Ip_Login_Section();

    QString get_ip();

    void set_ip(QString ip);

    int login_to_device();
    void logout_to_Device();

private:
    QJsonObject send_connect_Json_Synctes();
public slots:

    void timeout_to_device();

private:
    QString ip_;
    Qt_Json_Socket_Lib* lib;


};

#endif // IP_LOGIN_SECTION_H
