import QtQuick 2.15
import QtQuick.Controls 2.2

import treelistview 1.0 as T
import example 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Winner"

    property T.QmlTreeModelInterface treeModel

    FixedSizeTreeModel {
        id: fixedTree
    }


    T.TreeView {
        anchors.fill: parent
        rowDelegate: TreeRowDelegate{}
        id: projectView
        treeModel:fixedTree
    }

//    Rectangle {
//        anchors.fill: parent
//        color: "red"
//    }

//    T.TestItem {
//        anchors.fill: parent
//    }

//    MyTreeView.TestItem
//    {

//    }
}
