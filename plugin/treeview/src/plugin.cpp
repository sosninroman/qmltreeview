#include "plugin.h"

#include <QtQml/QtQml>

#include "treemodel.h"
#include "selector.h"
#include "qmltreeview.h"
#include "rowproperties.h"

namespace treeview
{

void TreeViewPlugin::registerTypes(const char* uri) {
    qmlRegisterUncreatableType<treeview::TreeModel>(uri, 1, 0, "TreeModel", "uncreatable type!");
    qRegisterMetaType<treeview::TreeModel*>("TreeModel");

    qmlRegisterType<treeview::Selector>(uri, 1, 0, "Selector");
    qRegisterMetaType<treeview::Selector*>("Selector");

    qmlRegisterType<treeview::QmlTreeView>(uri, 1, 0, "QmlTreeView");
    qRegisterMetaType<treeview::QmlTreeView*>("QmlTreeView");

    qmlRegisterType<treeview::RowProperties>(uri, 1, 0, "RowProperties");
    qRegisterMetaType<treeview::RowProperties*>("RowProperties");
}

}
