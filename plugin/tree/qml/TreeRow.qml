import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import tree 1.0

Row {
    id: row
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

    Item { //delegate margins
        width: expButton.width * modelData.nodeLevel
        height: expButton.height
    }

    Item { //expand icon
        id: expButton
        width: height
        height: delegateLdr.height
        Image {
            anchors.centerIn: parent
            width: expButton.width / 2
            height: expButton.height / 2
            source: "qrc:/icons/triangle.png"
            visible: modelData.expandable
            rotation: modelData.expanded ? 90 : 0
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                modelData.expanded = !modelData.expanded
                mouse.accepted = false
            }
            enabled: modelData.expandable
        }
    }

    Loader { //delegate
        id: delegateLdr
        Layout.fillWidth: true
        property var __modelData: modelData
        property var __index: index
        property var __selector: selector
        sourceComponent: rowDelegate
    }
}
