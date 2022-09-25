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

        focus: true
        Keys.onPressed: {
            event.accepted = false
            console.warn("TreeView: Key was pressed!")
        }

        onClicked: {
            selector.clear()
        }
    }

//    component TextWithFocus : TextArea {
//        id: txt
//        text: "text" + index
//        FocusScope {
//            id: innerScope
//            anchors.fill: parent
//            Keys.onPressed: {
//                console.warn(txt.text, "Inner FocusScope: Key was pressed!")
//            }
//            onFocusChanged: console.warn("focusChanged", focus)
//        }
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                console.warn("clicked")
//                innerScope.focus = true
//            }
//        }
//    }

//    component TextWithoutFocus : TextArea {
//        id: txtArea
//        Keys.onPressed: {
//            console.warn(txtArea.text, "Inner FocusScope: Key was pressed!")
//            event.accepted = false
//        }
//        onFocusChanged: console.warn("focusChanged", focus)
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                console.warn("clicked")
//                txtArea.focus = true
//            }
//        }
//    }

//    FocusScope {
//        id: rootScope
//        anchors.fill: parent
//        focus: true
//        Keys.onPressed: {
//            console.warn("Outer FocusScope: Key was pressed!")
//        }

//        width: col.width
//        height: col.height

//        Column {
//            id: col
//            TextWithoutFocus{
//                text: "1"
//            }
//            TextWithoutFocus {
//                text: "2"
//            }
//        }
//    }

//    ListView {
//        anchors.fill: parent

//        model: ListModel {
//            ListElement { name: "Bob" }
//            ListElement { name: "John" }
//            ListElement { name: "Michael" }
//        }

//        focus: true
//        Keys.onReturnPressed: {
//            event.accepted = false
//            console.warn("ListView: on return pressed")
//        }

//        delegate: FocusScope {
//            width: childrenRect.width; height: childrenRect.height
//            x:childrenRect.x; y: childrenRect.y
//            Loader {
//                sourceComponent: TextInput {
//                    focus: true
//                    text: name
//                    Keys.onReturnPressed: {
//                        event.accepted = false
//                        console.log(name)
//                    }
//                }
//            }
//        }
//    }

}
