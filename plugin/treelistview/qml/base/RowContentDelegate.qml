import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import treelistview 1.0

Delegate {
    id: item

    Connections {
        target: properties.selector
        function onSelectionChanged() {
            var i = 0
            while(i < properties.selector.selectedIndexes.length) {
                if(properties.currentIndex === properties.selector.selectedIndexes[i]) {
                    item.focus = true
                    return
                }
                i = i + 1
            }
            item.focus = false
        }
    }

    onClicked: {
        item.focus = true
    }

    onDoubleClicked: {
        if(properties.modelData.expandable) {
            properties.modelData.expanded = !properties.modelData.expanded
        }
    }
}
