import QtQuick 2.0

Rectangle {
    id: root

    // Propeerty can be setted from parent component. For continue using in inner Text component.
    property string displayText: ""
    // Property will be accesible from parent component.
    readonly property alias innerText: _firstText

    height: 100
    width: 100
    color: "lightgreen"
    border {
        color: "black"
        width: 1

    }
    radius: 10

    Text {
        id: _firstText
        anchors {
            centerIn: root
        }

        text: displayText
//        x: root.width / 2 - width / 2
//        y: root.height / 2 - height / 2
//        verticalAlignment: Text.AlignVCenter
//        horizontalAlignment: Text.AlignHCenter
        font {
            pointSize: Math.min(root.width, root.height) / 3
            bold: true
        }
    }
}
