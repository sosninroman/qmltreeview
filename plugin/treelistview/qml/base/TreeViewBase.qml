import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import treelistview 1.0
import "../private"

QmlTreeView {
    id: treeView

    onFocusChanged: scroll.focus = treeView.focus

    ScrollView {
        id: scroll
        anchors.fill: parent
        clip: true

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        Keys.onPressed: {
            if(event.key === Qt.Key_Up
                    || event.key === Qt.Key_Right
                    || event.key === Qt.Key_Left
                    || event.key === Qt.Key_Down) {
                treeView.Keys.pressed(event)
            }
        }

        contentWidth: col.width
        contentHeight: Math.max(col.height, treeView.height)
        wheelEnabled: true

        MouseArea { //area for mouse events dispatching
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.AllButtons

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

        Column { //tree view content
            id: col
            spacing: 0
            Repeater {
                model: treeView.model
                delegate: TreeNode {
                    row: index.row
                    parentIndex: view.rootIndex
                    view: treeView
                    contentWidth: scroll.contentWidth
                    selector: treeView.selector
                }
            }
        }
    }
}
