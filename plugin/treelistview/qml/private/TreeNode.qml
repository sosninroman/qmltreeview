import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

import QtQuick.Controls 2.12

import treelistview 1.0

FocusScope {
    id: nodeItem

    property var parentIndex
    property var row
    property Item view
    property var modelData
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
        modelData = !!view && !!view.treeModel ? view.treeModel.nodeData(currentIndex) : null
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

            width: Math.max(rowContent.width, view.width)
            height: rowContent.height + 2 * nodeItem.spacing
            Loader { //node background
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
                    onFocusChanged: {
                    }
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
                            item.initProperties(nodeItem, index)
                            item.initData()
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

    Component.onCompleted: {
        initData()
    }

}
