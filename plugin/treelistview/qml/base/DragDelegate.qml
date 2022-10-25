import QtQuick 2.15
import treelistview 1.0

Item {
    property TreeNodeProperties properties: __nodeProperties

    signal dropped(var drop, var hoveredModelData)
    signal entered(var drag, var hoveredModelData)
    signal exited(var hoveredModelData)
    signal positionChanged(var drag, var hoveredModelData)
}
