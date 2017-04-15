QT += qml quick widgets sql network testlib

CONFIG += c++11

SOURCES += main.cpp \
    sidebar_interface.cpp \
    tcp_connection.cpp \
    ip_login_section.cpp \
    boiler_controler_exception.cpp \
    adjust_device_contrler.cpp \
    qt_json_socket_lib.cpp \
    unit_test.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    qt_json_socket_lib_global.h \
    qt_json_socket_lib.h \
    sidebar_interface.h \
    tcp_connection.h \
    ip_login_section.h \
    boiler_controler_exception.h \
    adjust_device_contrler.h
