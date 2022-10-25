import QtQuick 2.15
import treelistview 1.0

Delegate {
    MouseArea {
        anchors.fill: parent
        onClicked: {
            properties.modelData.expanded = !properties.modelData.expanded
            mouse.accepted = false
        }
        enabled: properties.modelData.expandable
    }
}
