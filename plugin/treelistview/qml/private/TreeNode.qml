import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

import QtQuick.Controls 2.12

import treelistview 1.0

FocusScope {
    id: nodeItem

    TreeNodeProperties {
        id: nodeProperties
    }
    property alias properties: nodeProperties

//    property alias row: nodeProperties.row
    property alias view: nodeProperties.view
    property alias selector: nodeProperties.selector
    property alias parentIndex: nodeProperties.parentIndex
    property alias currentIndex: nodeProperties.currentIndex
    property alias childCount: nodeProperties.childCount
    property alias modelData: nodeProperties.modelData

    onModelDataChanged: {
        console.warn("data changed", modelData.name)
    }

    onChildCountChanged: {
        console.warn("children count changed", modelData.name, childCount)
        console.warn(modelData.expandable, modelData.expanded, (nodeItem.childCount > 0))
    }

//    function initProperties(parent, index) {
//        row = index
//        parentIndex = parent.currentIndex
//        view = parent.view
//        selector = parent.selector
//    }

//    function updateCurrentData() {
//        modelData = !!view && !!view.model ? view.model.nodeData(currentIndex) : null
//    }

//    function updateCurrentChildrenCount() {
//        childCount = !!view && !!view.model ? view.model.rowCount(currentIndex) : 0
//        updateCurrentData()
//    }

//    function onNodeDataChanged(ind){
//        if(currentIndex === ind) {
//            updateCurrentData()
//        }
//    }

//    function onNodeChildrenCountChanged(ind){
//        if(currentIndex === ind) {
//            updateCurrentChildrenCount()
//        }
//    }

//    function initData() {
//        console.warn("init begin")
//        if(!view) {
//            return
//        }
//        //FIXME
//        if(parentIndex) {
//            currentIndex = !!view && !!view.model ? view.model.index(row, 0, parentIndex) : null
//        }
//        else {
//            currentIndex = !!view && !!view.model ? view.model.index(row, 0) : null
//        }

//        updateCurrentData()
//        updateCurrentChildrenCount()

//        view.nodeDataChanged.connect(onNodeDataChanged)
//        view.nodeChildrenCountChanged.connect(onNodeChildrenCountChanged)
//        console.warn("init end")
//    }

    function checkMaxWidth() {
        if(rowContent.width > view._maxRowContentWidth) {
            view._maxRowContentWidth = rowContent.width
            view._maxWidthRowIndex = currentIndex
        }
    }

    Connections {
        target: view
        function onNeedToRecalcMaxRowWidth() {
            checkMaxWidth()
        }
    }

    focus: rowScope.focus || rp.hasFocus
    Keys.onPressed: {
        event.accepted = false
    }

    width: col.width
    height: col.height

    Column {
        id: col
        FocusScope { //row
            id: rowScope
            focus: rowContent.focus
            Keys.onPressed: {
                event.accepted = false
            }

            width: Math.max(view._maxRowContentWidth, view.width)
            height: rowContent.height + 2 * view.rowContentMargin

            Loader { //row background
                id: nodeBackgroundLdr

                anchors.fill: parent
                sourceComponent: view.backgroundDelegate

                property var __data: nodeItem.modelData
                property var __index: nodeItem.currentIndex
                property Selector __selector: nodeItem.selector
            }

            MouseArea { //area for mouse events dispatching
                anchors.fill: parent
                hoverEnabled: true
                acceptedButtons: Qt.AllButtons
                //TODO cursor shape

                onClicked: {
                    rowContent.onClicked(mouse)
                    if(nodeBackgroundLdr.item) {
                        nodeBackgroundLdr.item.clicked(mouse)
                    }
                    mouse.accepted = false
                }
                onDoubleClicked: {
                    rowContent.onDoubleClicked(mouse)
                    if(nodeBackgroundLdr.item) {
                        nodeBackgroundLdr.item.doubleClicked(mouse)
                    }
                }
                onEntered: {
                    rowContent.onEntered()
                    if(nodeBackgroundLdr.item) {
                        nodeBackgroundLdr.item.entered()
                    }
                }
                onExited: {
                    rowContent.onExited()
                    if(nodeBackgroundLdr.item) {
                        nodeBackgroundLdr.item.exited()
                    }
                }
                onPositionChanged: {
                    rowContent.onPositionChanged(mouse)
                    if(nodeBackgroundLdr.item) {
                        nodeBackgroundLdr.item.positionChanged(mouse)
                    }
                }
                onPressAndHold: {
                    rowContent.onPressAndHold(mouse)
                    if(nodeBackgroundLdr.item) {
                        nodeBackgroundLdr.item.pressAndHold(mouse)
                    }
                }
                onPressed: {
                    rowContent.onPressed(mouse)
                    if(nodeBackgroundLdr.item) {
                        nodeBackgroundLdr.item.pressed(mouse)
                    }
                }
                onReleased: {
                    rowContent.onReleased(mouse)
                    if(nodeBackgroundLdr.item) {
                        nodeBackgroundLdr.item.released(mouse)
                    }
                }
                onWheel: {
                    rowContent.onWheel(wheel)
                    if(nodeBackgroundLdr.item) {
                        nodeBackgroundLdr.item.wheel(wheel)
                    }
                    wheel.accepted = false
                }
            }

            TreeRow { //row content
                id: rowContent

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left

                modelData: nodeItem.modelData
                index: nodeItem.currentIndex
                selector: nodeItem.selector
                rowContentDelegate: view.rowContentDelegate
                expanderDelegate: view.expanderDelegate
                view: nodeItem.view

                onWidthChanged: {
                    if(view._maxWidthRowIndex === currentIndex) {
                        view.recalcMaxRowWidth()
                    }
                    else
                    {
                        checkMaxWidth()
                    }
                }
            }

            DropArea { //area for drop events processing
                anchors.fill: parent
                onDropped: {
                    if(drag.source.item) {
                        drag.source.item.dropped(drop, nodeItem.modelData)
                    }
                }
                onEntered: {
                    if(drag.source.item) {
                        drag.source.item.entered(drag, nodeItem.modelData)
                    }
                }
                onExited: {
                    if(drag.source.item) {
                        drag.source.item.exited(nodeItem.modelData)
                    }
                }
                onPositionChanged: {
                    if(drag.source.item) {
                        drag.source.item.positionChanged(drag, nodeItem.modelData)
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
                property Item __view: nodeItem.view
                property var __index: nodeItem.currentIndex
                property var __rowData: nodeItem.modelData
                sourceComponent: view.dragDelegate
            }
            Connections {
                target: dragHandler
                function onActiveChanged() {
                    dragDelegateLdr.Drag.drop()
                    dragDelegateLdr.active =  dragHandler.active
                }
            }
        }
        Column {
            visible: modelData.expandable && modelData.expanded && nodeItem.childCount > 0
            Repeater {
                id: rp
                model: childCount
                property bool hasFocus: false
                delegate: FocusScope {
                    focus: l.item.focus
                    Keys.onPressed: {
                        event.accepted = false
                    }

                    width: l.width
                    height: l.height
                    Loader {
                        id: l
                        focus: true
                        source: "TreeNode.qml"
                        onLoaded: {
//                            item.initProperties(nodeItem, index)
//                            item.initData()

                            item.properties.initialize(view, currentIndex, index)
                        }
                        Connections {
                            target: l.item
                            function onFocusChanged() {
                                if(l.item.focus) {
                                    rp.hasFocus = true
                                }
                                else {
                                    rp.hasFocus = false
                                    var i = 0
                                    while(i < rp.count) {
                                        if(rp.itemAt(i).item && rp.itemAt(i).item.focus){
                                            rp.hasFocus = true
                                            return
                                        }
                                        i = i + 1
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

//    Component.onCompleted: {
//        initData()
//    }
//    Component.onDestruction: {
//        view.nodeDataChanged.disconnect(onNodeDataChanged)
//        view.nodeChildrenCountChanged.disconnect(onNodeChildrenCountChanged)
//    }

}
