import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import treelistview 1.0

TreeView {
    nodeBackground: DefaultRowBackground {}

    onClicked: {
        selector.clear()
    }
}
