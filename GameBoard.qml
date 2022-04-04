import QtQuick 2.0
import Game 1.0

GridView {
    id: root
    model: GameBoardModel {
    }


    cellHeight: height / root.model.dimension
    cellWidth: width / root.model.dimension

    delegate: Item{
        id: _backgrounDelegate
        width: cellHeight
        height: cellWidth

        visible: display !== root.model.hiddenElementValue

        Tile {
            innerText.text: display
            anchors.fill: _backgrounDelegate
            anchors.margins: 5

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.model.move(index)
                }
            }
        }
    }

//    model:
}
