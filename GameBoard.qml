import QtQuick 2.0

GridView {
    id: root
    model: TilesModel {

    }


    cellHeight: height / 4
    cellWidth: width / 4

    delegate: Tile {
        innerText.text: display
        width: cellHeight
        height: cellWidth
    }

//    model:
}
