import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

import tree 1.0

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

//    Loader {
//        id: mouseHandlerLdr
//        sourceComponent: view.mouseHandlerComponent
//        property var __index: currentIndex
//        property var __data: nodeItem.nodeData
//        property Selector __selector: nodeItem.selector
//    }

    Item { //row
        width: Math.max(rowContent.width, nodeItem.contentWidth, view.width)
        height: rowContent.height + 2 * nodeItem.spacing
        Loader { //node background
            id: nodeBackgroundLdr
            anchors.fill: parent
            sourceComponent: view.nodeBackgroundComponent
            property var __data: nodeItem.nodeData
            property var __index: nodeItem.currentIndex
            property Selector __selector: nodeItem.selector
        }
        MouseArea { //node delegate
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.AllButtons
//            cursorShape: mouseHandlerLdr.item.cursorShape
            //TODO Connections MouseArea -> MouseHandlerLdr.item
//            Component.onCompleted: {
//                clicked.connect(mouseHandlerLdr.item.clicked)
//            }

            onClicked: {
                mouse.accepted = false
//                if (typeof mouseHandlerLdr.item.onClicked == 'function') {
//                    mouseHandlerLdr.item.onClicked(mouse, nodeData)
//                }
                rowContent.onClicked(mouse)
                nodeBackgroundLdr.item.clicked(mouse)
            }
            onDoubleClicked: {
                mouse.accepted = false
//                mouseHandlerLdr.item.onDoubleClick(mouse, nodeData)
                rowContent.onDoubleClicked(mouse)
                nodeBackgroundLdr.item.doubleClicked(mouse)
            }
            onEntered: {
//                if (typeof mouseHandlerLdr.item.onEntered == 'function') {
//                    mouseHandlerLdr.item.onEntered(nodeData)
//                }
                rowContent.onEntered()
                nodeBackgroundLdr.item.entered()
            }
            onExited: {
//                if (typeof mouseHandlerLdr.item.onExit == 'function') {
//                    mouseHandlerLdr.item.onExit(nodeData)
//                }
                rowContent.onExited()
                nodeBackgroundLdr.item.exited()
            }
            onPositionChanged: {
//                if (typeof mouseHandlerLdr.item.onPositionChanged == 'function') {
//                    mouseHandlerLdr.item.onPositionChanged(mouse)
//                }
                rowContent.onPositionChanged(mouse)
                nodeBackgroundLdr.item.positionChanged(mouse)
            }
            onPressAndHold: {
//                if (typeof mouseHandlerLdr.item.onPressAndHold == 'function') {
//                    mouseHandlerLdr.item.onPressAndHold(mouse)
//                }
                rowContent.onPressAndHold(mouse)
                nodeBackgroundLdr.item.pressAndHold(mouse)
            }
            onPressed: {
//                if (typeof mouseHandlerLdr.item.onPressed == 'function') {
//                    mouseHandlerLdr.item.onPressed(mouse)
//                }
                rowContent.onPressed(mouse)
                nodeBackgroundLdr.item.pressed(mouse)
            }
            onReleased: {
//                if (typeof mouseHandlerLdr.item.onReleased == 'function') {
//                    mouseHandlerLdr.item.onReleased(mouse)
//                }
                rowContent.onReleased(mouse)
                nodeBackgroundLdr.item.released(mouse)
            }
            onWheel: {
//                if (typeof mouseHandlerLdr.item.onWheel == 'function') {
//                    mouseHandlerLdr.item.onWheel(wheel)
//                }
                rowContent.onWheel(wheel)
                nodeBackgroundLdr.item.wheel(wheel)
            }

            TreeRowContent { //row content
                id: rowContent
                rowData: nodeItem.nodeData
                selector: nodeItem.selector
                rowDelegate: view.rowDelegate
                index: nodeItem.currentIndex
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
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
