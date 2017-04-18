#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ip_login_section.h"
#include "adjust_device_contrler.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    Ip_Login_Section* ip_login = new Ip_Login_Section;
    adjust_device_controler* contlorer = new adjust_device_controler;

    //qml을 바인딩함

    /*
     * 1. 바인딩할 오브젝트 목록
     *
     * 2. qml의 signal의 연결을 해야할 목록들
     *
     * 3. qml의 signal의 연결을 해야할 목록들
     *
     *
     */

    return app.exec();
}
