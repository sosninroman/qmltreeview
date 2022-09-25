import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

import treelistview 1.0

Column {
    id: nodeItem

    property var parentIndex
    property var row
    property Item view
    property var nodeData
    property int childCount: 0
    property var currentIndex
    property int spacing: 5
    property int contentWidth
    property Selector selector

    function initProperties(parent, index) {
        console.warn("init", parent, index)
        row = index
        parentIndex = parent.currentIndex
        spacing = parent.spacing
        view = parent.view
        contentWidth = Qt.binding(function(){return parent.contentWidth})
        selector = parent.selector
    }

    function updateCurrentData() {
        nodeData = !!view && !!view.treeModel ? view.treeModel.nodeData(currentIndex) : null
        childCount = !!view && !!view.treeModel ? view.treeModel.rowCount(currentIndex) : 0
    }

    function initData() {
        if(!view) {
            return
        }

        console.warn("init data", parentIndex, row)

        //FIXME
        if(parentIndex) {
            currentIndex = !!view && !!view.treeModel ? view.treeModel.index(row, 0, parentIndex) : null
        }
        else {
            currentIndex = !!view && !!view.treeModel ? view.treeModel.index(row, 0) : null
        }

        updateCurrentData()

        treeModel = view.treeModel
        treeModel.countChanged.connect(function(ind){
            if(currentIndex === ind) {
                childCount = 0
                updateCurrentData()
            }
        })

    }

    Item { //row
        //width: Math.max(rowContent.width, nodeItem.contentWidth, view.width)
        width: Math.max(rowContent.width, view.width)
        height: rowContent.height + 2 * nodeItem.spacing
        Loader { //node background
            id: nodeBackgroundLdr

            anchors.fill: parent
            sourceComponent: view.nodeBackgroundComponent

            property var __data: nodeItem.nodeData
            property var __index: nodeItem.currentIndex
            property Selector __selector: nodeItem.selector
        }
        TreeRow { //row content
            id: rowContent

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left

            modelData: nodeItem.nodeData
            index: nodeItem.currentIndex
            selector: nodeItem.selector
            rowDelegate: view.rowDelegate
        }
        MouseArea { //area for mouse events dispatching
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.AllButtons
//            cursorShape: mouseHandlerLdr.item.cursorShape

            onClicked: {
                rowContent.onClicked(mouse)
                nodeBackgroundLdr.item.clicked(mouse)
            }
            onDoubleClicked: {
                rowContent.onDoubleClicked(mouse)
                nodeBackgroundLdr.item.doubleClicked(mouse)
            }
            onEntered: {
                rowContent.onEntered()
                nodeBackgroundLdr.item.entered()
            }
            onExited: {
                rowContent.onExited()
                nodeBackgroundLdr.item.exited()
            }
            onPositionChanged: {
                rowContent.onPositionChanged(mouse)
                nodeBackgroundLdr.item.positionChanged(mouse)
            }
            onPressAndHold: {
                rowContent.onPressAndHold(mouse)
                nodeBackgroundLdr.item.pressAndHold(mouse)
            }
            onPressed: {
                rowContent.onPressed(mouse)
                nodeBackgroundLdr.item.pressed(mouse)
            }
            onReleased: {
                rowContent.onReleased(mouse)
                nodeBackgroundLdr.item.released(mouse)
            }
            onWheel: {
                rowContent.onWheel(wheel)
                nodeBackgroundLdr.item.wheel(wheel)
            }
        }
        DropArea { //area for drop events processing
            anchors.fill: parent
            onEntered: {
                if(drag.source.item) {
                    drag.source.item.processRowEntering(drag, nodeItem.nodeData)
                }
            }
            onExited: {
                if(drag.source.item) {
                    drag.source.item.processRowExiting(nodeItem.nodeData)
                }
            }
            onDropped: {
                if(drag.source.item) {
                    drag.source.item.processDropping(drop, nodeItem.nodeData)
                }
            }
        }
        DragHandler { //drag events handler
            id: dragHandler
            target: dragDelegateLdr
        }
        Loader { //drag delegate
            id: dragDelegateLdr
            active: false
            Drag.active: dragDelegateLdr.active
            property var __index: nodeItem.currentIndex
            property var __rowData: nodeItem.nodeData
            property Item __view: nodeItem.view
            sourceComponent: rowContent.delegateItem.dragDelegate
        }
        Connections {
            target: dragHandler
            function onActiveChanged() {
                dragDelegateLdr.Drag.drop()
                dragDelegateLdr.active =  dragHandler.active
            }
        }
    }

    Loader { //child nodes
        sourceComponent: ColumnLayout {
            spacing: 0
            Repeater {
                model: childCount
                delegate: Loader {
                    source: "TreeNode.qml"
                    onLoaded: {
                        item.initProperties(nodeItem, index)
                        item.initData()
                    }
                }
            }
        }
        visible: nodeData.expandable && nodeData.expanded && nodeItem.childCount > 0
    }

    Component.onCompleted: {
        initData()
    }

}
