import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import tree 1.0

Row {
    property var rowData
    property Selector selector
    property Component rowDelegate
    property var index
    property alias delegateItem: delegateLdr.item

    function onClicked(mouse) {
        delegateLdr.item.clicked(mouse)
    }
    function onDoubleClicked(mouse) {
        delegateLdr.item.doubleClicked(mouse)
    }
    function onEntered() {
        delegateLdr.item.entered()
    }
    function onExited() {
        delegateLdr.item.exited()
    }
    function onPositionChanged(mouse) {
        delegateLdr.item.positionChanged(mouse)
    }
    function onPressAndHold(mouse) {
        delegateLdr.item.pressAndHold(mouse)
    }
    function onPressed(mouse) {
        delegateLdr.item.pressed(mouse)
    }
    function onReleased(mouse) {
        delegateLdr.item.released(mouse)
    }
    function onWheel(wheel) {
        delegateLdr.item.wheel(wheel)
    }

    Item { //delegate margins
        width: expButton.width * rowData.nodeLevel
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
            visible: rowData.expandable
            rotation: rowData.expanded ? 90 : 0
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                rowData.expanded = !rowData.expanded
                mouse.accepted = false
            }
            enabled: rowData.expandable
        }
    }

    Loader { //delegate
        id: delegateLdr
        Layout.fillWidth: true
        property var __rowData: rowData
        property var __selector: selector
        property var __index: index
        sourceComponent: rowDelegate
    }
}
