import QtQuick 2.15
import treelistview 1.0
import "./private"

InputHandler {
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
