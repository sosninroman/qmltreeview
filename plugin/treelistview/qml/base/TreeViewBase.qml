import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml.Models 2.12
import treelistview 1.0
import "../private"

QmlTreeView {
    id: treeView

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

    property int availableWidth: width - (treeView.height < scroll.contentHeight ? vbar.width : 0)
    onAvailableWidthChanged: {
        console.warn("changed", availableWidth)
    }

    Loader { //vertical scroll bar
        id: vbar
        sourceComponent: scrollBarDelegate
        active: treeView.height < scroll.contentHeight
        visible: active

        onWidthChanged: console.warn("width changed", width)

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        onLoaded: {
            item.orientation = Qt.Vertical
            updateVScrollBarSize()
//            item.onPositionChanged.connect(function(){
//                if(item.pressed) {
//                    scroll.contentY = item.position * scroll.height
//                }
//            })
        }
    }

    Loader { //horizontal scroll bar
        id: hbar
        sourceComponent: scrollBarDelegate
        active: treeView.availableWidth < scroll.contentWidth

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        onLoaded: {
            item.orientation = Qt.Horizontal
            updateHScrollBarSize()
//            item.onPositionChanged.connect(function(){
//                if(item.pressed) {
//                    scroll.contentX = item.position * scroll.height
//                }
//            })
        }
    }

    Flickable {
        id: scroll
        //anchors.fill: parent
        //anchors.rightMargin: scroll.height < scroll.contentHeight ? vbar.width : 0
        //anchors.bottomMargin: hbar.height
        anchors.left: treeView.left
        anchors.top: treeView.top
        anchors.right: treeView.right
        anchors.rightMargin: vbar.active ? vbar.width : 0
        anchors.bottom: hbar.active ? hbar.bottom : treeView.bottom
        //anchors.bottomMargin: hbar.active ? hbar.width : 0
        clip: true

        boundsBehavior: Flickable.StopAtBounds
        //interactive: false

        onContentHeightChanged: treeView.updateVScrollBarSize()
        onContentWidthChanged: treeView.updateHScrollBarSize()
        onHeightChanged: treeView.updateVScrollBarSize()
        onWidthChanged: treeView.updateHScrollBarSize()
        onContentYChanged: {
            if(!!vbar.item && !vbar.item.pressed)
            {
                treeView.updateVScrollBarPosition()
            }
        }
        onContentXChanged: {
            if(!!hbar.item && !hbar.item.pressed)
            {
                treeView.updateHScrollBarPosition()
            }
        }

        Connections {
            target: vbar
            function onVisibleChanged() {
                console.warn("vbar visible changed", vbar.visible)
            }
        }

        contentWidth: col.width
        contentHeight: Math.max(col.height, treeView.height)
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
