#include <QGuiApplication>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QVariant>
#include "main_process.h"




int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    QQmlComponent component ( &engine, QUrl(QStringLiteral ("qrc:/main.qml")));
    QObject* root_obj = component.create ();

    /*Main_Process* progress = new Main_Process;

    progress->set_root_qml_object (root_obj);

    progress->init_main_object ();

    progress->init_signal ();*/



    //로그인 윈도우 오브젝트를 먼저 세팅해둠
    /*
     * 1. 바인딩할 오브젝트 목록
     *
     * 2. qml의 signal의 연결을 해야할 목록들
     *
     * 3. qml의 signal와 같이 qml의 변수들을 연결
     *
     *
     *
     *
     */


    return app.exec();
}
