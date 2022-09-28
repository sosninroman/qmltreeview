import QtQuick 2.15
import "./base"

ExpanderDelegateBase {
    id: expButton

    property alias source: img.source

    Image {
        id: img
        anchors.centerIn: parent
        width: expButton.width / 2
        height: expButton.height / 2
        visible: modelData.expandable
        rotation: modelData.expanded ? 90 : 0
    }
}
