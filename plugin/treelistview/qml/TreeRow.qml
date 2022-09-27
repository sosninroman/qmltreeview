import QtQuick 2.15
import QtQuick.Layouts 1.12
import treelistview 1.0

FocusScope {
    property var modelData
    property var index
    property Selector selector

    property Component rowDelegate
    property alias delegateItem: delegateLdr.item

    function onClicked(mouse) {
        delegateItem.clicked(mouse)
    }
    function onDoubleClicked(mouse) {
        delegateItem.doubleClicked(mouse)
    }
    function onEntered() {
        delegateItem.entered()
    }
    function onExited() {
        delegateItem.exited()
    }
    function onPositionChanged(mouse) {
        delegateItem.positionChanged(mouse)
    }
    function onPressAndHold(mouse) {
        delegateItem.pressAndHold(mouse)
    }
    function onPressed(mouse) {
        delegateItem.pressed(mouse)
    }
    function onReleased(mouse) {
        delegateItem.released(mouse)
    }
    function onWheel(wheel) {
        delegateItem.wheel(wheel)
    }

    width: row.width
    height: row.height

    focus: delegateLdr.item.focus
    Keys.onPressed: {
        event.accepted = false
    }

    Row {
        id: row
        Item { //delegate margins
            width: expButton.width * modelData.nodeLevel
            height: expButton.height
        }

        RowExpanderDelegateBase {
            id: expButton
            width: height
            height: delegateLdr.height
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    modelData.expanded = !modelData.expanded
                    mouse.accepted = false
                }
                enabled: modelData.expandable
            }
        }

        Loader { //content delegate
            id: delegateLdr
            Layout.fillWidth: true
            property var __modelData: modelData
            property var __index: index
            property var __selector: selector
            sourceComponent: rowDelegate
            focus: true
        }
    }
}
