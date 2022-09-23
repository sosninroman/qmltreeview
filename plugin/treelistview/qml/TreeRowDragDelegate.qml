import QtQuick 2.15

Item {
    id: dragDelegate

    property var index: __index
    property var rowData: __rowData
    property Item view: __view

    function processRowEntering(drag, hoveredData) {}

    function processRowExiting(hoveredData) {}

    function processDropping(drop, hoveredData) {}

    function getCursorShape(hoveredData) {
        return Qt.ArrowCursor
    }
}
