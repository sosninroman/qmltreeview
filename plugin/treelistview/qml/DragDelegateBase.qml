import QtQuick 2.15

Item {
    property Item view: __view
    property var index: __index
    property var modelData: __rowData

    signal dropped(var drop, var hoveredModelData)
    signal entered(var drag, var hoveredModelData)
    signal exited(var hoveredModelData)
    signal positionChanged(var drag, var hoveredModelData)
}
