import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import treelistview 1.0
import "../private"

QmlTreeView {
    id: treeView

    onFocusChanged: scroll.focus = treeView.focus

    property Component scrollBarDelegate : ScrollBar {
        active: true

        onActiveChanged: {
            if (!active) {
                active = true
            }
        }
    }

    function updateVScrollBarSize() {
        if(vbar.active) {
            vbar.item.size = scroll.height / scroll.contentHeight
            updateVScrollBarPosition()
        }
    }

    function updateHScrollBarSize() {
        if(hbar.active) {
            hbar.item.size = scroll.width / scroll.contentWidth
            updateHScrollBarPosition()
        }
    }

    function updateVScrollBarPosition() {
        if(vbar.active) {
            vbar.item.position = scroll.visibleArea.yPosition
        }
    }

    function updateHScrollBarPosition() {
        if(hbar.active) {
            hbar.item.position = scroll.visibleArea.xPosition
        }
    }

    Loader {
        id: vbar
        sourceComponent: scrollBarDelegate
        active: treeView.height < scroll.contentHeight

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        onLoaded: {
            item.orientation = Qt.Vertical
            updateVScrollBarSize()
        }
    }

    Loader {
        id: hbar
        sourceComponent: scrollBarDelegate
        active: treeView.width < scroll.contentWidth

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        onLoaded: {
            item.orientation = Qt.Horizontal
            updateHScrollBarSize()
        }
    }

    Flickable {
        id: scroll
        anchors.fill: parent
        anchors.rightMargin: scroll.height < scroll.contentHeight ? vbar.width : 0
        anchors.bottomMargin: hbar.height
        clip: true

        boundsBehavior: Flickable.StopAtBounds
        //interactive: false

        onContentHeightChanged: treeView.updateVScrollBarSize()
        onContentWidthChanged: treeView.updateHScrollBarSize()
        onHeightChanged: treeView.updateVScrollBarSize()
        onWidthChanged: treeView.updateHScrollBarSize()
        onContentYChanged: treeView.updateVScrollBarPosition()
        onContentXChanged: treeView.updateHScrollBarPosition()

        Keys.onPressed: {
            if(event.key === Qt.Key_Up
                    || event.key === Qt.Key_Right
                    || event.key === Qt.Key_Left
                    || event.key === Qt.Key_Down) {
                treeView.Keys.pressed(event)
            }
        }

        contentWidth: col.width - (scroll.height < scroll.contentHeight ? vbar.width : 0)
        contentHeight: Math.max(col.height, treeView.height) - hbar.height
        //wheelEnabled: true

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
                    id: topLevelNode
                    Component.onCompleted: {
                        topLevelNode.properties.initialize(treeView, parentIndex, index.row)
                    }
                }
            }
        }
    }
}
