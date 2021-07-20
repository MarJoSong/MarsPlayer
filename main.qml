import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import com.huahua.marsplayer 1.0

Window {
   // id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World");

    Button {
        id: demoNum
        x: 100
        y: 100
        width: 250
        height: 100
        text: qsTr("Click Me")
        onClicked: {
            MainApp.testFunc()
        }
    }

    Text {
        id: text
        x: 400
        y: 400
        text: ""+MainApp.demoNum
        color: "#ff0000"
        font.pixelSize: 50
    }
}
