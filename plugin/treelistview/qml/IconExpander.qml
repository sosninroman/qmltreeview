import QtQuick 2.15
import "./base"

ExpanderDelegate {
    id: expButton

    property alias source: img.source

    Image {
        id: img
        anchors.centerIn: parent
        width: expButton.width / 2
        height: expButton.height / 2
        visible: properties.modelData.expandable
        rotation: properties.modelData.expanded ? 90 : 0
    }
}
