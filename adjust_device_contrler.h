#ifndef ADJUST_DEVICE_CONTRLER_H
#define ADJUST_DEVICE_CONTRLER_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include "tcp_connection.h"
#include "boiler_controler_exception.h"


class device_control{
public:
    device_control();
    virtual ~device_control();

    virtual void set_device_name(QString name)                   = 0;
    virtual void set_device_type(QString type)                   = 0;
    virtual void set_device_gpio(int gpio)                       = 0;
    virtual void set_device_owner_phone_number(QString number)   = 0;

    virtual QString get_device_name()                            = 0;
    virtual QString get_device_type()                            = 0;
    virtual int     get_device_gpio()                            = 0;
    virtual QString get_device_owner_phone_number()              = 0;


    virtual int add_device()                                     = 0;
    virtual int remove_device(int pid)                           = 0;
    virtual int update_device_info(int pid)                      = 0;
    virtual int check_device_state()                             = 0;
    virtual int add_auto_upgrade_code()                          = 0;

};

class adjust_device_controler : public QObject, public device_control
{
    Q_OBJECT
public:
    explicit adjust_device_controler(QObject *parent = 0)         ;
    virtual ~adjust_device_controler()                            ;

    virtual void set_device_name(QString name)                   ;
    virtual void set_device_type(QString type)                   ;
    virtual void set_device_gpio(int gpio)                       ;
    virtual void set_device_owner_phone_number(QString number)   ;

    virtual QString get_device_name()                            ;
    virtual QString get_device_type()                            ;
    virtual int     get_device_gpio()                            ;
    virtual QString get_device_owner_phone_number()              ;


    virtual int add_device()                                     ;
    virtual int remove_device(int pid)                           ;
    virtual int update_device_info(int pid)                      ;
    virtual int check_device_state()                             ;
    virtual int add_auto_upgrade_code()                          ;

    int set_device_tempture(int pid, int tempture)              ;
    int get_device_tempture(int pid)                            ;

signals:

public slots:

private:
    QJsonObject add_device_json_form();
    QJsonObject remove_device_json_form(QString pid);
    QJsonObject update_device_json_form(QString pid);
    QJsonObject set_device_tempture_json_form(QString pid, int tempture);
    QJsonObject get_device_tempture_json_form(QString pid);


private:
    QSqlDatabase db_;

    tcp_connection net_con;

    QString temp_name_;
    QString temp_device_type_;
    int temp_device_gpio_;
    QString owner_phone_number_;

};

#endif // ADJUST_DEVICE_CONTRLER_H
