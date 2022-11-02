#include "plugin.h"

#include <QtQml/QtQml>

#include "treemodel.h"
#include "selector.h"
#include "qmltreeview.h"
#include "rowproperties.h"

void Plugin::registerTypes(const char* uri) {
    qmlRegisterUncreatableType<QmlTreeModelInterface>(uri, 1, 0, "QmlTreeModelInterface", "uncreatable type!");
    qRegisterMetaType<QmlTreeModelInterface*>("QmlTreeModelInterface");

    qmlRegisterType<Selector>(uri, 1, 0, "Selector");
    qRegisterMetaType<Selector*>("Selector");

    qmlRegisterType<QmlTreeView>(uri, 1, 0, "QmlTreeView");
    qRegisterMetaType<QmlTreeView*>("QmlTreeView");

    qmlRegisterType<RowProperties>(uri, 1, 0, "RowProperties");
    qRegisterMetaType<RowProperties*>("RowProperties");
}
