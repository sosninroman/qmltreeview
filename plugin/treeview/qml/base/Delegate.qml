import QtQuick 2.15
import treeview 1.0

FocusScope {
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

    property RowProperties properties: __nodeProperties
}
