import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import com.huahua.marsplayer 1.0

Window {
    id: mywindow
    visible: true
    /*
    //全屏无边框
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    flags: Qt.FramelessWindowHint
    */
    width: 320
    height: 240
    flags: Qt.FramelessWindowHint
    title: qsTr("Mars Player");
    property bool fullscreen: true
    property string language: {
        mywindow.title = qsTr("Mars Player")
    }
    property int controlAreaButtonWidth: 28
    property int controlAreaButtonHeight: 28
    property color controlAreaButtonPressedColor: "#265F99"
    property color controlAreaButtonUnpressedColor: "#AACC00"

    MouseArea{
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        property point clickPos: "0, 0"

        onPressed: {
            if(mouse.button === Qt.LeftButton){
                clickPos = Qt.point(mouseX, mouseY)
            }
        }
        onPositionChanged: {
            if(pressed){
                var mousePos = Qt.point(mouseX-clickPos.x, mouseY-clickPos.y)
                mywindow.setX(mywindow.x+mousePos.x)
                mywindow.setY(mywindow.y+mousePos.y)
            }
        }
    }

    MarsPlayer {
        id: msplayer
    }

    //
    Image {
        id: backGroundImg
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        source: msplayer.backGround ? "file:///" + msplayer.backGround : ""
        smooth: true
    }

    Button {
        id: changeSkinBtn
        x: 10
        y: 17
        width: mywindow.controlAreaButtonWidth
        height: mywindow.controlAreaButtonHeight
        text: qsTr("Click Me")
        opacity: 0.5
        contentItem: Image {
            width: parent.width
            height: parent.height
            source: "qrc:/image/image/changeSkin.png"
            fillMode: Image.PreserveAspectCrop
        }
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: changeSkinBtn.down ? mywindow.controlAreaButtonPressedColor : mywindow.controlAreaButtonUnpressedColor
            radius: 4
        }
        onClicked: {
            chooseSkinDlg.open()
        }
    }

    //
    FileDialog {
        id: chooseSkinDlg
        title: qsTr("Choose the picture")
        folder: msplayer.backGroundPath ? "file:///" + msplayer.backGroundPath : shortcuts.desktop
        nameFilters: [qsTr("Image files(*.png*.jgp*.bmp)"), qsTr("All files(*)")]
        onAccepted: {
            console.log(backGroundImg.source)
            backGroundImg.source = chooseSkinDlg.fileUrl
            msplayer.changeBackGround(chooseSkinDlg.fileUrl.toString().substring(8, chooseSkinDlg.fileUrl.length))
            console.log("you choose " + chooseSkinDlg.fileUrl)
        }
        onRejected: {
            console.log("canceled")
        }
    }
}
