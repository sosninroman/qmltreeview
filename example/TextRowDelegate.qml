import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import treelistview 1.0 as T

T.TextRowContent {
    property Component nameDialog

    Keys.onPressed: {
        console.warn(properties.modelData.name, "Delegate: Key was pressed!")
        event.accepted = true
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
                        properties.view.model.addChild(properties.modelData.index, nameDialogObj.name)
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
                        properties.modelData.name = nameDialogObj.name
                    }
                })
            }
        }
        MenuItem {
            text: "Remove"
            onTriggered: {
                properties.view.model.removeNode(properties.modelData.index)
                properties.selector.clear()
            }
        }
    }

    onClicked: {
        if(mouse.button === Qt.RightButton) {
            contextMenu.popup(mouse.x, mouse.y)
        }
    }
}
