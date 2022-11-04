import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import treeview 1.0 as T

T.DragDelegate {
    Row {
        spacing: 10
        Item {
            width: 15
        }
        Label {
            id: txt
            text: properties.modelData.name
            leftPadding: 15
        }
    }
    onDropped: {
        console.warn("drop \"", properties.modelData.name, "\" to \"", hoveredModelData.name, "\"")
        properties.view.model.moveNode(hoveredModelData.index, properties.index)
        properties.selector.clearSelection();
    }
}
