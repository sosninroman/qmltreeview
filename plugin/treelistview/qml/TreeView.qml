import "./base"

TreeViewBase {
    backgroundDelegate: RowBackground {}
    onClicked: {
        selector.clear()
        focus = true
    }
}
