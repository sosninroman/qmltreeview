import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import treeview 1.0

Delegate {
    id: item

    property int leftMargin: 0
    property int topMargin: 0
    property int rightMargin: 0
    property int bottomMargin: 0

    Connections {
        target: properties.selector
        function onSelectionChanged() {
            var i = 0
            while(i < properties.selector.selectedIndexes.length) {
                if(properties.index === properties.selector.selectedIndexes[i]) {
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
