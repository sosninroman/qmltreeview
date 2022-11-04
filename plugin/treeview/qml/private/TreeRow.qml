import QtQuick 2.15
import QtQuick.Layouts 1.12
import treeview 1.0
import "../"

FocusScope {
    property RowProperties properties

    property var modelData: properties.modelData

    property alias contentItem: contentLdr.item

    function onClicked(mouse) {
        contentItem.clicked(mouse)
    }
    function onDoubleClicked(mouse) {
        contentItem.doubleClicked(mouse)
    }
    function onEntered() {
        contentItem.entered()
    }
    function onExited() {
        contentItem.exited()
    }
    function onPositionChanged(mouse) {
        contentItem.positionChanged(mouse)
    }
    function onPressAndHold(mouse) {
        contentItem.pressAndHold(mouse)
    }
    function onPressed(mouse) {
        contentItem.pressed(mouse)
    }
    function onReleased(mouse) {
        contentItem.released(mouse)
    }
    function onWheel(wheel) {
        contentItem.wheel(wheel)
    }

    width: row.width
    height: row.height

    focus: contentLdr.item.focus
    Keys.onPressed: {
        event.accepted = false
    }

    onWidthChanged: {
        if(properties.view._maxWidthRowIndex === properties.index) {
            properties.view.recalcMaxRowWidth()
        }
        else
        {
            properties.checkMaxWidth(width)
        }
    }

    Row {
        id: row
        Item { //delegate margins
            width: expanderLdr.width * modelData.nodeLevel
            height: expanderLdr.height
        }

        Loader { //expander
            id: expanderLdr
            width: height
            height: contentLdr.height
            property RowProperties __nodeProperties: properties
            sourceComponent: properties.view.expanderDelegate
        }

        Loader { //content delegate
            id: contentLdr
            Layout.fillWidth: true
            property RowProperties __nodeProperties: properties
            sourceComponent: properties.view.rowContentDelegate
            focus: true
        }
    }
}
