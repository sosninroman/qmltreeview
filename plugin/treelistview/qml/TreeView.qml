import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import treelistview 1.0

FocusScope {
    id: treeView
    property QmlTreeModelInterface treeModel
    property Component rowDelegate
    property Component nodeBackgroundComponent: RowBackgroundDelegateBase {}
    property Selector selector: Selector {}

    property int delegateSpacing: 3

    property int treeRowCount: treeModel.rowCount( treeModel.rootIndex() )

    signal canceled()
    signal clicked(var mouse)
    signal doubleClicked(var mouse)
    signal entered()
    signal exited()
    signal positionChanged(var mouse)
    signal pressAndHold(var mouse)
    signal pressed(var mouse)
    signal released(var mouse)
    signal wheel(var wheel)

    Connections {
        target: treeModel
        function onModelReset() {
            treeView.treeRowCount = 0
            treeView.treeRowCount = treeModel.rowCount( treeModel.rootIndex() )
        }
    }

    ScrollView {
        id: scroll
        anchors.fill: parent
        clip: true

        focus: true
        Keys.onPressed: {
            console.warn("ScrollView: Key was pressed!")
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

        ColumnLayout {
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
                    Component.onCompleted: console.warn("index", index)
                }
            }
        }
    }
}
