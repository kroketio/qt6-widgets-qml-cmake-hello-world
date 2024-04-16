import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs


Rectangle {
    id: root

    signal example(int status)

    visible: true
    color: "red"
    anchors.fill: parent

    Image {
        width: 320
        height: 320
        source: "qrc:/assets/rabbit.png"

        Text {
            color: "white"
            text: "clickme"
            font.pointSize: 18
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.example(707)
            }
        }
    }
}