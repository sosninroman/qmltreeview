import QtQuick 2.15
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import treelistview 1.0 as T
import example 1.0

ApplicationWindow {
    id: appWindow
    visible: true
    width: 640
    height: 480
    title: "Tree View Example Application"

    property T.QmlTreeModelInterface treeModel

    FixedSizeTreeModel {
        id: stringTree
    }

    property Component nameDialog: Dialog {
        title: "Enter a name"
        standardButtons: Dialog.Ok | Dialog.Cancel

        anchors.centerIn: parent

        property alias name: nameInput.text

        contentItem: Frame {
            TextInput {
                id: nameInput
                anchors.fill: parent
            }
        }

        visible: false
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
                        console.warn(nameDialogObj.name)
                        if(nameDialogObj.name.length > 0) {
                            var modelData = stringTree.nodeData(view.selector.selectedIndexes[0])
                            console.warn(modelData.name)
                            modelData.name = nameDialogObj.name
                        }
                    })
                }
                highlighted: hovered
            }
            ToolButton {
                text: "Up"
                enabled: view.selector.hasSelection
                highlighted: hovered
            }
            ToolButton {
                text: "Down"
                enabled: view.selector.hasSelection
                highlighted: hovered
            }
            Item {
                Layout.fillWidth: true
            }
        }
    }

//    menuBar: MenuBar {
//        Menu {
//            title: "Edit"
//            Action {
//                text: "Add a child"
//                enabled: view.selector.hasSelection
//                onTriggered: {
//                    nameDialog.visible = true
//                }
//            }
//        }
//    }

    T.DefaultTreeView {
        id: view
        anchors.fill: parent
        rowContentDelegate: TextRowDelegate{}
        dragDelegate: RowDragDelegate{}
        expanderDelegate: T.IconExpander {
            source: "qrc:/icons/triangle.png"
        }

        treeModel: stringTree

        focus: true
        Keys.onPressed: {
            event.accepted = false
            console.warn("TreeView: Key was pressed!")
        }
//        Keys.onReleased: {
//            event.accepted = false
//            console.warn("TreeView: Key was released!")
//        }
        Keys.onUpPressed: console.warn("up pressed!")
    }
}
