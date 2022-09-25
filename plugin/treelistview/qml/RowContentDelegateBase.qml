import QtQuick 2.15
import treelistview 1.0

FocusScope {
    id: rowDelegate

    property var index: __index
    property var modelData: __modelData
    property Selector selector: __selector

    property TreeRowDragDelegate dragDelegate: null

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
