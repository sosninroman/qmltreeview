#include "plugin.h"

#include <QtQml/QtQml>

#include "treemodel.h"
#include "selector.h"
#include "treehelper.h"
#include "qmltreeview.h"
#include "treenodeproperties.h"

void Plugin::registerTypes(const char* uri) {
    qmlRegisterUncreatableType<QmlTreeModelInterface>(uri, 1, 0, "QmlTreeModelInterface", "uncreatable type!");
    qRegisterMetaType<QmlTreeModelInterface*>("QmlTreeModelInterface");

    qmlRegisterType<Selector>(uri, 1, 0, "Selector");
    qRegisterMetaType<Selector*>("Selector");

    qmlRegisterSingletonType<TreeHelper>(uri, 1, 0, "TreeHelper", &TreeHelper::instance);

    qmlRegisterType<QmlTreeView>(uri, 1, 0, "QmlTreeView");
    qRegisterMetaType<QmlTreeView*>("QmlTreeView");

    qmlRegisterType<TreeNodeProperties>(uri, 1, 0, "TreeNodeProperties");
    qRegisterMetaType<TreeNodeProperties*>("TreeNodeProperties");
}
