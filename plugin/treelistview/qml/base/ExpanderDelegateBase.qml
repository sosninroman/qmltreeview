import QtQuick 2.15
import treelistview 1.0

DelegateBase {
    id: expander

//    onClicked: {
//        modelData.expanded = !modelData.expanded
//        mouse.accepted = false
//    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            modelData.expanded = !modelData.expanded
            mouse.accepted = false
        }
        enabled: modelData.expandable
    }
}
