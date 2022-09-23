import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

import treelistview 1.0

Item {
    id: treeView
    property QmlTreeModelInterface treeModel
    property Component rowDelegate
    property Component nodeBackgroundComponent: TreeNodeBackground {}

    property int delegateSpacing: 3

    property int treeRowCount: treeModel.rowCount( treeModel.rootIndex() )

    Connections {
        target: treeModel
        function onModelReset() {
            treeView.treeRowCount = 0
            treeView.treeRowCount = treeModel.rowCount( treeModel.rootIndex() )
        }
    }

    Selector {
        id: viewSelector
    }

    ScrollView {
        id: scroll
        anchors.fill: parent
        clip: true

        property var rootIndex
        property var topLevelNodesCount

        Component.onCompleted: {
            rootIndex = treeModel.rootIndex()
            topLevelNodesCount = treeModel.rowCount(rootIndex)
        }

        ColumnLayout {
            spacing: 0
            Repeater {
                model: treeView.treeModel
                delegate: TreeNode {
                    row: index
                    parentIndex: scroll.rootIndex
                    spacing: delegateSpacing
                    view: treeView
                    contentWidth: scroll.contentWidth
                    selector: viewSelector
                }
            }
        }
    }
}
