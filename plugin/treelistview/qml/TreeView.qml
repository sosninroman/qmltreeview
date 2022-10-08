import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import treelistview 1.0
import "./private"

QmlTreeView {
    id: treeView
    property QmlTreeModelInterface treeModel
    property Component rowContentDelegate
    property Component backgroundDelegate
    property Component dragDelegate
    property Component expanderDelegate

    property int delegateSpacing: 3

    onFocusChanged: scroll.focus = treeView.focus

    //focus: true

    //1. ScrollView grabs row events
    //2. ScrollView doesn't scroll by mouse
    ScrollView {
        id: scroll
        anchors.fill: parent
        clip: true

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
             ScrollBar.vertical.policy: ScrollBar.AlwaysOn

//        focus: false
//        onActiveFocusChanged: console.warn("active focus = ", activeFocus)
//        Keys.onUpPressed: console.warn("up pressed! (scroll view)")
//        Keys.forwardTo: treeView

        property var rootIndex
        property var topLevelNodesCount

        Component.onCompleted: {
            rootIndex = treeModel.rootIndex()
            topLevelNodesCount = treeModel.rowCount(rootIndex)
        }

        contentWidth: col.width
        contentHeight: Math.max(col.height, height)
        wheelEnabled: true

        MouseArea { //area for mouse events dispatching
            width: scroll.width
            height: scroll.height
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
                wheel.accepted = false
            }
        }

        Column {
            id: col
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
