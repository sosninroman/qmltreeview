import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import treelistview 1.0
import "./private"

InputHandler {
    id: treeView
    property QmlTreeModelInterface treeModel
    property Component rowContentDelegate
    property Component backgroundDelegate
    property Component dragDelegate
    property Component expanderDelegate
    property alias selector: selector

    property int delegateSpacing: 3

    property int treeRowCount: treeModel.rowCount( treeModel.rootIndex() )

    Connections {
        target: treeModel
        function onModelReset() {
            treeView.treeRowCount = 0
            treeView.treeRowCount = treeModel.rowCount( treeModel.rootIndex() )
        }
    }

    Selector {
        id: selector
    }

    ScrollView {
        id: scroll
        anchors.fill: parent
        clip: true

        focus: true
        Keys.onPressed: {
            event.accepted = true
            treeView.Keys.pressed(event)
        }

        property var rootIndex
        property var topLevelNodesCount

        Component.onCompleted: {
            rootIndex = treeModel.rootIndex()
            topLevelNodesCount = treeModel.rowCount(rootIndex)
        }

        MouseArea { //area for mouse events dispatching
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.AllButtons
//            cursorShape: mouseHandlerLdr.item.cursorShape

            onClicked: {
                treeView.clicked(mouse)
            }
            onDoubleClicked: {
                treeView.doubleClicked(mouse)
            }
            onEntered: {
                treeView.entered()
            }
            onExited: {
                treeView.exited()
            }
            onPositionChanged: {
                treeView.positionChanged(mouse)
            }
            onPressAndHold: {
                treeView.pressAndHold(mouse)
            }
            onPressed: {
                treeView.pressed(mouse)
            }
            onReleased: {
                treeView.released(mouse)
            }
            onWheel: {
                treeView.wheel(wheel)
            }
        }

        Column {
            spacing: 0
            Repeater {
                model: treeView.treeModel
                delegate: TreeNode {
                    row: index.row
                    parentIndex: scroll.rootIndex
                    spacing: delegateSpacing
                    view: treeView
                    contentWidth: scroll.contentWidth
                    selector: treeView.selector
                }
            }
        }
    }
}
