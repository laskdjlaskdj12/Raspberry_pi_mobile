#include "main_process.h"

Main_Process::Main_Process(QObject *parent) : QObject(parent),\
    root_obj(nullptr),\
    main_window_obj(nullptr),\
    login_window_obj(nullptr),\
    loading_screen_obj(nullptr),\
    account_panel_info_obj(nullptr),\
    main_indicator_panel_obj(nullptr),\
    add_device_obj(nullptr)
{
    ip_login = new Ip_Login_Section;

    controler  = new adjust_device_controler;

    if (QSqlDatabase::contains ("Client_device_list")){
        db_ = QSqlDatabase::database ("Client_device_list");

    } else {

        db_ = QSqlDatabase::addDatabase ("QSQLITE","Client_device_list");
        db_.setDatabaseName ("Client_device_list.db");
    }

}
Main_Process::~Main_Process(){

    ip_login->deleteLater ();
    controler->deleteLater ();
    root_obj->deleteLater ();
    main_window_obj->deleteLater ();
    login_window_obj->deleteLater ();
    loading_screen_obj->deleteLater ();
    account_panel_info_obj->deleteLater ();
    main_indicator_panel_obj->deleteLater ();
    add_device_obj->deleteLater ();

}

int Main_Process::init_main_object ()
{
    try{

        if (root_obj == nullptr){

            throw QString("root_obj property is not setting");
        }

        main_window_obj = root_obj->findChild<QObject*>("main_window_obj");

        login_window_obj = main_window_obj->findChild<QObject*>("login_window_obj");

        loading_screen_obj = main_window_obj->findChild<QObject*>("loading_screen_obj");

        account_panel_info_obj = main_window_obj->findChild<QObject*>("account_penl_obj");

        main_indicator_panel_obj = main_window_obj->findChild<QObject*>("main_indicator_panel_obj");

        add_device_obj = main_window_obj->findChild<QObject*>("device_add_panel_obj");

        panel_menu_obj = main_indicator_panel_obj->findChild<QObject*>("boiler_main_panel");

        list_view_delegate_obj = panel_menu_obj->findChild<QObject*>("listView");

        dial_delegate_obj = list_view_delegate_obj->findChild<QObject*>("dial_delegate");

        return 0;
    }
    catch(QString& e){

        qDebug()<<"[Error] : "<<e;
        return -1;
    }
}

//qml에서 emit된 시그널들을 현재 클래스의 slot으로 connect시킴
int Main_Process::init_signal()
{
    //LoginWindow를 connect시킴
    QObject::connect (login_window_obj, SIGNAL(req_acc_dev(QString)), this, SLOT(check_ip_connect(QString)));

    //Device_add_obj를 connect시킴
    QObject::connect (add_device_obj, SIGNAL(add_raspberry_Device(QString, int, QString)), this, SLOT(add_raspberry_device(QString,int,QString)));

    //Boiler_Indicator_panel ( main_indicator_panel_obj ) 에서 디바이스 제거시
    QObject::connect (main_indicator_panel_obj, SIGNAL(remove_device_pid(QString)), this, SLOT(remove_raspberry_device (QString)));

    //tempture가 바귀었을때
    QObject::connect (dial_delegate_obj, SIGNAL(change_tempture(int, QString, int)), this, SLOT(set_device_tempture(int,QString,int)));

}

void Main_Process::set_root_qml_object(QObject *obj)
{
    root_obj = obj;
}

QObject *Main_Process::get_root_qml_object()
{
    return root_obj;
}







// ========================== slot Area ==========================
void Main_Process::ip_connect_to_raspberry(QString ip)
{
    try{
        /*
     * 1. states를 loading_screen으로 변경
     * 2. Ip_Login_Section으로 ip 로그인 요청
     * 3. 만약 IP_Login_Section이 fail일경우 Login_page로 변경후 에러메세지를 출력함
     * 4. 로그인이 성공적일경우 Login_Loading_Page 에서 Main_Panel_Page로 변경함
     * 5. 디바이스 목록들을 불러서 로딩
     * 6. 만약 디바이스 목록 리턴값이 fail일 경우 Login_page로 변경후 에러메세지를 출력함
     * 7. JsonObject로 리턴시 Device_List에 저장
     * 8. Device_List 에서 모든 디바이스들을 db에 저장
     * */

        //states 를 loadingscreen으로 변경
        main_window_obj -> setProperty ("state", "Login_Loading_Page");

        //받은 ip으로 ip를 요청함
        ip_login->set_ip (ip);
        if (ip_login->login_to_device () < 0){


            main_window_obj -> setProperty ("state", "Login_Page");

            //만약 ip의 접속이 fail일 경우 login_page로 변경후 에러메세지를 출력함
            login_window_obj->findChild<QObject*> ("error_edit")->setProperty ("text", "Error of connect of raspberry");

            return;
        }

        //ip연결이 성공시 main_indicator로 state를 변경함
        main_window_obj -> setProperty ("state", "main_indicator_panel_obj");

        //디바이스 목록을 로딩
        QJsonObject _device_list_ = controler -> load_device_list ();

        //만약 디바이스 목록리턴값이 fail일경우 Login_Loading_Page 으로 변경후 에러메세지를 출력함
        if (_device_list_["Error"].isNull () == false){

            main_window_obj -> setProperty ("state", "Login_Page");

            login_window_obj->findChild<QObject*> ("error_edit")->setProperty ("text", "Error of Receiving Device Data From Server");
        }

        //JsonArray의 파라미터들을 분석해서 각 Array마다
        QJsonArray _d_array_ = _device_list_["device_list"].toArray ();

        //QJsonArray를 루프 돌려서 QJsonValue로 패널 오브젝트에 add_device() 자바스크립트 파라미터를 input함
        foreach (const QJsonValue& v, _d_array_) {

            QJsonObject _it_obj_ = v.toObject ();

            //메인 패널에서 프로퍼티를 가지고 옴
            int _qml_list_size_parameter_ = main_indicator_panel_obj->property ("panel_count").toInt ();

            //qml에 온도계 파라미터
            int _qml_tempture_parameter_ = (_it_obj_["d_range"].toInt () / _it_obj_["d_max_range"].toInt ()) * 100 ;

            //리턴 밸류는 없음
            QVariant _return_value_;

            //디바이스 메인 패널오브젝트에 add_device() 자바스크립트 파라미터를 input하고 실행함
            QMetaObject::invokeMethod(main_indicator_panel_obj, "add_device",
                                      Q_RETURN_ARG(QVariant, _return_value_),                   //return 값은 NULL
                                      Q_ARG(int, _qml_list_size_parameter_),          //Panel_index
                                      Q_ARG(QString, _it_obj_["d_name"].toString ()), //Device_name_string
                    Q_ARG(int, _qml_tempture_parameter_),                             //Current_tempture
                    Q_ARG(int, 0),                                                    //Setting_tempture
                    Q_ARG(QString, _it_obj_["d_pid"].toString ()));                   //Device_pid

            //디바이스 패널을 저장할 db
            QSqlQuery _device_db_query_ (db_);

            _device_db_query_.prepare ("INSERT INTO `Device_list`(`device_type`, `device_name`, `device_pid`, `device_gpio`, `access_mobile_number`, `device_active`)"
                                       "VALUES (:type, :name, :pid, :gpio, :access_mobile, :device_active);");

            _device_db_query_.bindValue (":type", _it_obj_["d_type"].toString ());
            _device_db_query_.bindValue (":name", _it_obj_["d_name"].toString ());
            _device_db_query_.bindValue (":pid",  _it_obj_["d_pid"].toString ());
            _device_db_query_.bindValue (":gpio", _it_obj_["d_gpio"].toString ());
            _device_db_query_.bindValue (":access_mobile", 0);
            _device_db_query_.bindValue (":device_active",(int)true);

            //디바이스 db에 정상적으로 input함
            if( _device_db_query_.exec () == false){    throw _device_db_query_.lastError ();}

        }

    }catch(QSqlError& e){
        qDebug()<<"[Error] : "<<e.text ();
    }
}

void Main_Process::add_raspberry_device(QString d_name, int d_gpio, QString d_type)
{
    /*
     * 1. contlorer->add_device()함수를 호출해서 디바이스를 추가함
     * 2. pid는 해당 디바이스 리스트 패널에 넣음
     * 3. 입력되고 나고 만약 추가가 안될경우 Error문구를 device_add_page에 있는 라벨로 통해서 전송함
     * 4. 성공적으로 add가 될경우 자바스크립트의 add_device()로 넣음
     * 5. states를 main_panel_page_obj으로 전환
     * */

    try{
        int _ret_pid_ = 0;

        controler->set_device_name (d_name);
        controler->set_device_gpio (d_gpio);
        controler->set_device_type (d_type);

        _ret_pid_ = controler->add_device ();

        if( _ret_pid_ < 0){
            throw QString("Error of adding_device");

        }

        //리턴밸류는 없음
        QVariant _return_value_;

        //qml 패널 맥시멈 크기
        int _qml_list_size_parameter_ = main_indicator_panel_obj->property ("panel_count").toInt ();

        //자바스크립트에 add_device()를 호출
        QMetaObject::invokeMethod(main_indicator_panel_obj, "add_device",
                                  Q_RETURN_ARG(QVariant, _return_value_),//return 값은 NULL
                                  Q_ARG(int, _qml_list_size_parameter_), //Panel_index
                                  Q_ARG(QString, d_name),                //Device_name_string
                                  Q_ARG(int, 0),                         //Current_tempture
                                  Q_ARG(int, 0),                         //Setting_tempture
                                  Q_ARG(QString, QString::number (_ret_pid_)));                    //Device_pid
        //state를 Main_State로 변경함
        main_indicator_panel_obj->setProperty ("states", "Main_state");



    }catch(QString &e){

        main_indicator_panel_obj->setProperty ("err_tag", " Error of adding device from server : " + e);
    }

}

void Main_Process::remove_raspberry_device(QString pid)
{
    /*
     * 1. 각 디바이스 패널에 remove버튼이 emit될시 pid를 remove
     * 2. 자바스크립트 제거루틴은 미리 제거루틴을 실행함 --> 제거루틴 코드 생성 안해도됨
     * 3. 만약 remove가 fail일시 remove하지 않고 해당 버튼의 색을 변경
     * */
    try{

        if ( controler->remove_device (pid.toInt ()) < 0){
            throw QString("Error of remove device protocol");
        }

    }catch(QString &e){

        //디바이스 오브젝트의 로그를 출력
        add_device_obj->setProperty ("device_states_label", e);
    }
}

void Main_Process::set_device_tempture(int tempture, QString pid, int index)
{
    /*
     * 1. 해당 pid의 db 쿼리로 검색후 value를 저장
     * 2. 해당 value를 세팅후 전송
     * 3. value가 정상적일때 change_device_tempture 의 자바스크립트를 실행
     * 4. setting_tempture를 받아온 값의 setting_tempture를 변경
     * 5. 문제 : device_tempture의 패널 index를 어떻게 main_panel의 object로 전송받을수 있는지
     * */
    try{

        if( controler->set_device_tempture (pid.toInt (), tempture) < 0){

            throw QString("Error of set_tempture device protocol");
        }

        QVariant _return_value_;

        QMetaObject::invokeMethod(main_indicator_panel_obj, "change_device_tempture",
                                  Q_RETURN_ARG(QVariant, _return_value_),//return 값은 NULL
                                  Q_ARG(int, index),                       //Panel_index
                                  Q_ARG(int, tempture));                   //Device_tempture

    }catch(QString &e){

        //디바이스 오브젝트의 로그를 출력
        add_device_obj->setProperty ("device_states_label", e);
    }
}
