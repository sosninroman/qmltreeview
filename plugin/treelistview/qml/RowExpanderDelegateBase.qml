import QtQuick 2.15
import treelistview 1.0

Item {
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

    Image {
        anchors.centerIn: parent
        width: expButton.width / 2
        height: expButton.height / 2
        source: "qrc:/icons/triangle.png"
        visible: modelData.expandable
        rotation: modelData.expanded ? 90 : 0
    }

    onClicked: {
        modelData.expanded = !modelData.expanded
        mouse.accepted = false
    }
}