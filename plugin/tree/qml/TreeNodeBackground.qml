import QtQuick 2.15
import QtQml.Models 2.12

import tree 1.0

Rectangle {
    id: background

    property var index: __index
    property var data: __data
    property Selector selector: __selector

    opacity: 0.2

    signal canceled()
    signal clicked(var mouse)
    signal doubleClicked(var mouse)
    signal entered()
    signal exited()
    signal positionChanged(var mouse)
    signal pressAndHold(var mouse)
    signal pressed(var mouse)
    signal released(var mouse)
    signal wheel(var wheel)

    function checkState() {
        if(!selector && !index)
        {
            state = "default"
        }
        else if( selector.isSelected(index) ) {
            state = "selected"
        }
        else if(selector.currentIndex === index ) {
            state = "hovered"
        }
        else
        {
            state = "default"
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

    state: "default"

    states: [
        State {
            name: "default"
            PropertyChanges { target: background; color: "transparent" }
        },
        State {
            name: "hovered"
            PropertyChanges { target: background; color: "blue"; opacity: 0.3 }
        },
        State {
            name: "selected"
            PropertyChanges { target: background; color: "blue"; opacity: 0.5 }
        }
    ]
}
