import QtQuick 2.15
import tree 1.0

Item {
    id: rowDelegate

    property var index: __index
    property var rowData: __rowData
    property TreeRowDragDelegate dragDelegate: null
    property Selector selector: __selector

    signal canceled()
    signal clicked(var mouse)
    signal doubleClicked(var mouse)
    signal entered()
    signal exited()
    signal positionChanged(var mouse)
    signal pressAndHold(var mouse)
    signal pressed(var mouse)
    signal released(var mouse)
    signal wheel(var wheel)
}
