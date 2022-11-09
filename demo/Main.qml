import QtQuick 2.15
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import treeview 1.0 as T
import demo 1.0

ApplicationWindow {
    id: appWindow
    visible: true
    width: 640
    minimumWidth: 320
    height: 480
    minimumHeight: 240
    title: "Tree View Demo"

    property Component nameDialog: Dialog {
        title: "Enter a name"

        anchors.centerIn: parent
        standardButtons: Dialog.Ok | Dialog.Cancel
        closePolicy: Popup.CloseOnEscape
        modal: true
        focus: true

        property alias name: nameInput.text

        contentItem: TextField {
            id: nameInput
            focus: true
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "Add a child"
                enabled: view.selector.hasSelection
                onClicked: {
                    var nameDialogObj = nameDialog.createObject(appWindow)
                    nameDialogObj.open()
                    nameDialogObj.accepted.connect(function() {
                        if(nameDialogObj.name.length > 0) {
                            stringTree.addChild(view.selector.selectedIndexes[0], nameDialogObj.name)
                        }
                    })
                }
                highlighted: hovered
            }
            ToolButton {
                text: "Rename"
                enabled: view.selector.hasSelection
                onClicked: {
                    var nameDialogObj = nameDialog.createObject(appWindow)
                    nameDialogObj.open()
                    nameDialogObj.accepted.connect(function() {
                        if(nameDialogObj.name.length > 0) {
                            var modelData = stringTree.nodeData(view.selector.selectedIndexes[0])
                            modelData.name = nameDialogObj.name
                        }
                    })
                }
                highlighted: hovered
            }
            ToolButton {
                text: "Remove"
                enabled: view.selector.hasSelection
                onClicked: {
                    stringTree.removeNode(view.selector.selectedIndexes[0])
                    view.selector.clear()
                }
                highlighted: hovered
            }
            Item {
                Layout.fillWidth: true
            }
        }
    }

    T.TreeView {
        id: view
        anchors.fill: parent

        backgroundDelegate: T.RowBackground{}
        rowContentDelegate: TextRowDelegate{
            nameDialog: appWindow.nameDialog
        }
        dragDelegate: RowDragDelegate{}
        expanderDelegate: T.IconExpander {
            expandedIconSource: "qrc:/icons/triangle_expanded.png"
            collapsedIconSource: "qrc:/icons/triangle_collapsed.png"
        }

        model: EditableStringsTreeModel {
            id: stringTree
        }

        focus: true
        Keys.onPressed: {
            event.accepted = false
            console.warn("TreeView: Key was pressed!")
        }
    }
}
