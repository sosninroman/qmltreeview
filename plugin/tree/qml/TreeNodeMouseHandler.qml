import QtQml 2.15
import QtQml.Models 2.15
import QtQuick 2.15

import tree 1.0

Item {
    property var index: __index
    property var data: __data
    property Selector selector: __selector
    property var cursorShape: Qt.ArrowCursor

    signal clicked(var mouse)

    function select() {
        selector.clearSelection()
        selector.select(index)
    }

//    function onClicked(mouse, nodeData) {
//        select()
//    }
    function onClicked(mouse) {
        select()
    }
    function onDoubleClick(mouse, nodeData) {
        if(data.expandable) {
            data.expanded = !data.expanded
        }
    }
    function onEntered(nodeData) {
        selector.setCurrentIndex(index)
    }
    function onExit(nodeData) {
        selector.clearCurrentIndex()
    }
}
