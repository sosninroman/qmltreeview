import QtQuick 2.15
import treeview 1.0
import "./base"

Delegate {

    property color defaultColor: "transparent"
    property real defaultOpacity: 1
    property color hoveringColor: "grey"
    property real hoveringOpacity: 0.3
    property color selectionColor: "grey"
    property real selectionOpacity: 0.5

    function checkState() {
        if(!properties.selector && !properties.index)
        {
            background.state = "default"
        }
        else if( properties.selector.isSelected(properties.index) ) {
            background.state = "selected"
        }
        else if(properties.selector.currentIndex === properties.index ) {
            background.state = "hovered"
        }
        else
        {
            background.state = "default"
        }
    }

    Connections {
        target: properties.selector
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
                PropertyChanges { target: background; color: defaultColor; opacity: defaultOpacity}
            },
            State {
                name: "hovered"
                PropertyChanges { target: background; color: hoveringColor; opacity: hoveringOpacity }
            },
            State {
                name: "selected"
                PropertyChanges { target: background; color: selectionColor; opacity: selectionOpacity }
            }
        ]
    }
}
