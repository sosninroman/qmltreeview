import QtQuick 2.15
import QtQml.Models 2.12
import treeview 1.0
import "../private"

QmlTreeView {
    id: treeView

    availableWidth: width - (treeView.height < scroll.contentHeight ? vbar.width : 0)

    function scrollByWheel(wheel){
        var isHorizontal = wheel.modifiers & Qt.AltModifier
        if(!isHorizontal){
            scrollHorizontal(wheel)
        }
        else {
            scrollVertical(wheel)
        }
    }

    function scrollHorizontal(wheel) {
        if(scroll.contentHeight <= scroll.height) {
            return
        }
        var newContentY = scroll.contentY - (wheel.angleDelta.y / 8) * scrollVelocity
        if(newContentY < 0) {
            newContentY = 0
        }
        var maxVerticalShift = (scroll.contentHeight - scroll.height)
        if(newContentY > maxVerticalShift) {
            newContentY = maxVerticalShift
        }
        scroll.contentY = newContentY
    }

    function scrollVertical(wheel) {
        if(scroll.contentWidth <= scroll.width) {
            return
        }
        var newContentX = scroll.contentX - (wheel.angleDelta.x / 8) * scrollVelocity
        if(newContentX < 0) {
            newContentX = 0
        }
        var maxHorizontalShift = (scroll.contentWidth - scroll.width)
        if(newContentX > maxHorizontalShift) {
            newContentX = maxHorizontalShift
        }
        scroll.contentX = newContentX
    }

    Loader { //vertical scroll bar
        id: vbar
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        function updateSize() {
            if(!!vbar.item && vbar.active) {
                vbar.item.size = scroll.height / scroll.contentHeight
                vbar.updatePosition()
            }
        }

        function updatePosition() {
            if(vbar.active) {
                vbar.item.position = scroll.visibleArea.yPosition
            }
        }

        sourceComponent: scrollBarDelegate
        active: treeView.height - (hbar.active ? hbar.height : 0) < scroll.contentHeight
        onLoaded: {
            item.orientation = Qt.Vertical
            vbar.updateSize()
            item.onPositionChanged.connect(function(){
                if(item.pressed) {
                    scroll.contentY = item.position * scroll.contentHeight
                }
            })
        }
    }

    Loader { //horizontal scroll bar
        id: hbar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        function updatePosition() {
            if(hbar.active) {
                hbar.item.position = scroll.visibleArea.xPosition
            }
        }

        function updateSize() {
            if(!!hbar.item && hbar.active) {
                hbar.item.size = scroll.width / scroll.contentWidth
                hbar.updatePosition()
            }
        }

        sourceComponent: scrollBarDelegate
        active: treeView.availableWidth < scroll.contentWidth
        onLoaded: {
            item.orientation = Qt.Horizontal
            hbar.updateSize()
            item.onPositionChanged.connect(function(){
                if(item.pressed) {
                    scroll.contentX = item.position * scroll.contentWidth
                }
            })
        }
    }

    Flickable {
        id: scroll
        anchors.fill: parent
        anchors.rightMargin: vbar.active ? vbar.width : 0
        anchors.bottomMargin: hbar.active ? hbar.height : 0
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        interactive: false
        onContentHeightChanged: {
            vbar.updateSize()
        }
        onContentWidthChanged: {
            hbar.updateSize()
        }
        onHeightChanged: {
            vbar.updateSize()
        }
        onWidthChanged: {
            hbar.updateSize()
        }
        onContentYChanged: {
            if(!!vbar.item && !vbar.item.pressed)
            {
                vbar.updatePosition()
            }
        }
        onContentXChanged: {
            if(!!hbar.item && !hbar.item.pressed)
            {
                hbar.updatePosition()
            }
        }
        contentWidth: col.width
        contentHeight: col.height
        Column { //tree view content
            id: col
            spacing: 0
            Repeater {
                model: treeView.model
                delegate: TreeNode {
                    id: topLevelNode
                    Component.onCompleted: {
                        topLevelNode.properties.initialize(treeView, treeView.rootIndex, index.row)
                    }
                }
            }
        }
    }
    MouseArea { //area for mouse events dispatching
        anchors.bottom: treeView.bottom
        anchors.right: treeView.right
        anchors.left: treeView.left
        anchors.rightMargin: vbar.active ? vbar.width : 0
        anchors.bottomMargin: hbar.active ? hbar.height : 0
        height: scroll.height - scroll.contentHeight

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
            treeView.scrollByWheel(wheel)
        }
    }
}
