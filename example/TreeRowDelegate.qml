import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import tree 1.0 as T

T.TreeRowDelegateBase {
    id: textCell

    height: rect.height
    width: rect.width

    Rectangle {
        id: rect
        height: lbl.height
        width: lbl.width
        color: "green"
        Label {
            id: lbl
            text: modelData.name
            font.pixelSize: 12
        }
    }

    function select() {
        selector.clearSelection()
        selector.select(index)
    }

    onEntered: {
        selector.setCurrentIndex(index)
    }

    onExited: {
        selector.clearCurrentIndex()
    }

    onClicked: {
        select()
    }

    onDoubleClicked: {
        if(modelData.expandable) {
            modelData.expanded = !modelData.expanded
        }
    }
}
