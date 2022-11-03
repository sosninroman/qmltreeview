import QtQuick 2.15
import "./base"

ExpanderDelegate {
    id: expButton

    property string expandedIconSource
    property string collapsedIconSource

    Image {
        id: img
        source: properties.modelData.expanded ? expandedIconSource : collapsedIconSource
        anchors.centerIn: parent
        width: expButton.width / 2
        height: expButton.height / 2
        visible: properties.modelData.expandable
    }
}
