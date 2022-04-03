import QtQuick 2.0

GridView {
    id: root
    model: TilesModel {

    }


    cellHeight: height / 4
    cellWidth: width / 4

    delegate: Item{
        id: _backgrounDelegate
        width: cellHeight
        height: cellWidth

        visible: display != "16"

        Tile {
            innerText.text: display
            anchors.fill: _backgrounDelegate
            anchors.margins: 5
        }
    }

//    model:
}
