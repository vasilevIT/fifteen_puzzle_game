import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: root
    width: 480
    height: 480
    visible: true
    title: qsTr("Hello World")

    GameBoard {
        anchors.fill: parent
    }
}
