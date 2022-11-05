import QtQuick.Controls 2.15
import "./base"
import treeview 1.0

TreeViewBase {
    scrollBarDelegate : ScrollBar {
            active: true

            onActiveChanged: {
                if (!active) {
                    active = true
                }
            }
        }
    backgroundDelegate: RowBackground {}
    onClicked: {
        selector.clear()
        focus = true
    }
}
