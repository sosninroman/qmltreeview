import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import treelistview 1.0 as T

T.DragDelegateBase {
    Row {
        spacing: 10
        Item {
            width: 15
        }
        Label {
            id: txt
            text: modelData.name
            leftPadding: 15
        }
    }
    onDropped: {
        console.warn("drop \"", modelData.name, "\" to \"", hoveredModelData.name, "\"")
    }
}
