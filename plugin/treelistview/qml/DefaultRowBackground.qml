import QtQuick 2.15
import treelistview 1.0
import "./base"

RowBackgroundDelegateBase {
    function checkState() {
        if(!selector && !index)
        {
            background.state = "default"
        }
        else if( selector.isSelected(index) ) {
            background.state = "selected"
        }
        else if(selector.currentIndex === index ) {
            background.state = "hovered"
        }
        else
        {
            background.state = "default"
        }
    }

    Connections {
        target: selector
        function onCurrentChanged(curIndex, prevIndex) {
            checkState()
        }
        function onSelectionChanged() {
            checkState()
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent

        opacity: 0.2
        state: "default"

        states: [
            State {
                name: "default"
                PropertyChanges { target: background; color: "transparent" }
            },
            State {
                name: "hovered"
                PropertyChanges { target: background; color: "grey"; opacity: 0.3 }
            },
            State {
                name: "selected"
                PropertyChanges { target: background; color: "grey"; opacity: 0.5 }
            }
        ]
    }
}
