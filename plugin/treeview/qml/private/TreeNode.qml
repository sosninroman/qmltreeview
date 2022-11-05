import QtQuick 2.15
import QtQml.Models 2.12

import QtQuick.Controls 2.12

import treeview 1.0

FocusScope {
    id: nodeItem

    RowProperties {
        id: nodeProperties
    }
    property alias properties: nodeProperties
    property alias view: nodeProperties.view

    Connections {
        target: view
        function onNeedToRecalcMaxRowWidth() {
            properties.checkMaxWidth(rowContent.width)
        }
    }

    focus: rowScope.focus || rp.hasFocus
    Keys.onPressed: event.accepted = false

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

            width: Math.max(view._maxRowContentWidth, view.availableWidth)

            height: rowContent.height //+ view.rowContentTopMargin + view.rowContentBottomMargin

            Loader { //row background
                id: nodeBackgroundLdr
                anchors.fill: parent
                sourceComponent: view.backgroundDelegate
                property RowProperties __nodeProperties: nodeItem.properties
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
                    view.scrollByWheel(wheel)
                }
            }

            TreeRow { //row content
                id: rowContent
                //y: parent.y + view.rowContentTopMargin
                anchors.left: parent.left
                properties: nodeItem.properties
            }

            DropArea { //area for drop events processing
                anchors.fill: parent
                onDropped: {
                    if(drag.source.item) {
                        drag.source.item.dropped(drop, properties.modelData)
                    }
                }
                onEntered: {
                    if(drag.source.item) {
                        drag.source.item.entered(drag, properties.modelData)
                    }
                }
                onExited: {
                    if(drag.source.item) {
                        drag.source.item.exited(properties.modelData)
                    }
                }
                onPositionChanged: {
                    if(drag.source.item) {
                        drag.source.item.positionChanged(drag, properties.modelData)
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
                property RowProperties __nodeProperties: nodeItem.properties
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
        Column { //child nodes
            visible: properties.modelData.expandable && properties.modelData.expanded && properties.childrenCount > 0
            Repeater {
                id: rp
                model: properties.childrenCount
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
                            item.properties.initialize(view, properties.index, index)
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
}
