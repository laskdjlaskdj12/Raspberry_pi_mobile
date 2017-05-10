#ifndef BOILER_CONTROLER_EXCEPTION_H
#define BOILER_CONTROLER_EXCEPTION_H

#include <QObject>
#include <QString>
#include <QDebug>

class Boiler_Controler_Exception
{
public:
    Boiler_Controler_Exception(QString e, int line);
    void get_error();
    QString get_error_string();
    int     get_line();



private:
    QString err_;
    int line_;

};

#endif // BOILER_CONTROLER_EXCEPTION_H
