import QtQuick 2.15
import QtQuick.Controls 2.15
import "./base"

RowContentDelegate {
    id: item

    property string role: "name"

    height: rect.height
    width: rect.width

    Rectangle {
        id: rect
        height: lbl.height
        width: lbl.width
        color: item.focus ? "green" : "transparent"
        Label {
            id: lbl
            text: properties.modelData[role]
            font.pixelSize: 12
        }
    }

    function select() {
        properties.selector.clearSelection()
        properties.selector.select(properties.currentIndex)
    }

    onEntered: {
        properties.selector.setCurrentIndex(properties.currentIndex)
    }

    onExited: {
        properties.selector.clearCurrentIndex()
    }

    onClicked: {
        select()
    }
}
