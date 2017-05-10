import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2


ApplicationWindow {
    visible: true
    width: 375
    height: 667

    Main_Window{
        id: main_window
        objectName: "main_window_obj"
        width: parent.width
        height: parent.height
    }
}
