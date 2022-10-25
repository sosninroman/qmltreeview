import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import treelistview 1.0 as T

T.Delegate {
    id: textCell

    height: rect.height
    width: rect.width

    property Component nameDialog

    Rectangle {
        id: rect
        height: lbl.height
        width: lbl.width
        color: textCell.focus ? "green" : "transparent"
        Label {
            id: lbl
            text: properties.modelData.name
            font.pixelSize: 12
        }
    }

    Keys.onPressed: {
        console.warn(properties.modelData.name, "Delegate: Key was pressed!")
        event.accepted = true
    }

    Connections {
        target: properties.selector
        function onSelectionChanged() {
            var i = 0
            while(i < properties.selector.selectedIndexes.length) {
                if(properties.currentIndex === properties.selector.selectedIndexes[i]) {
                    textCell.focus = true
                    return
                }
                i = i + 1
            }
            textCell.focus = false
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

    Menu {
        id: contextMenu
        MenuItem {
            text: "Add new child"
            onTriggered: {
                var nameDialogObj = nameDialog.createObject(appWindow)
                nameDialogObj.open()
                nameDialogObj.accepted.connect(function() {
                    if(nameDialogObj.name.length > 0) {
                        properties.view.model.addChild(modelData.index, nameDialogObj.name)
                    }
                })
            }
        }
        MenuItem {
            text: "Rename"
            onTriggered: {
                var nameDialogObj = nameDialog.createObject(appWindow)
                nameDialogObj.open()
                nameDialogObj.accepted.connect(function() {
                    if(nameDialogObj.name.length > 0) {
                        modelData.name = nameDialogObj.name
                    }
                })
            }
        }
        MenuItem {
            text: "Remove"
            onTriggered: {
                view.model.removeNode(modelData.index)
                selector.clear()
            }
        }
    }

    onClicked: {
        select()
        textCell.focus = true
        if(mouse.button === Qt.RightButton) {
            contextMenu.popup(mouse.x, mouse.y)
        }
    }

    onDoubleClicked: {
        if(properties.modelData.expandable) {
            properties.modelData.expanded = !properties.modelData.expanded
        }
    }
}
