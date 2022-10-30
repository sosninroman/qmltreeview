import QtQuick.Controls 2.15
import "./base"

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
