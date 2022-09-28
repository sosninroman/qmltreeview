import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import treelistview 1.0 as T

T.RowContentDelegateBase {
    id: textCell

    height: rect.height
    width: rect.width

    Rectangle {
        id: rect
        height: lbl.height
        width: lbl.width
        color: textCell.focus ? "green" : "transparent"
        Label {
            id: lbl
            text: modelData.name
            font.pixelSize: 12
        }
    }

    Keys.onPressed: {
        console.warn(modelData.name, "Delegate: Key was pressed!")
        event.accepted = true
    }

    Connections {
        target: selector
        function onSelectionChanged() {
            var i = 0
            while(i < selector.selectedIndexes.length) {
                if(index === selector.selectedIndexes[i]) {
                    textCell.focus = true
                    return
                }
                i = i + 1
            }
            textCell.focus = false
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
        textCell.focus = true
    }

    onDoubleClicked: {
        if(modelData.expandable) {
            modelData.expanded = !modelData.expanded
        }
    }
}