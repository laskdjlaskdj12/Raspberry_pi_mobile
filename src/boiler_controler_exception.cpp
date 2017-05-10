#include "boiler_controler_exception.h"

Boiler_Controler_Exception::Boiler_Controler_Exception(QString e, int line):err_(e)\
  ,line_(line)
{}

void Boiler_Controler_Exception::get_error()
{
    qDebug()<<"[Error_String] : "<<err_;
    qDebug()<<"[Error_Line] : "<< line_;
}

QString Boiler_Controler_Exception::get_error_string(){ return err_;}

int Boiler_Controler_Exception::get_line(){ return line_;}
