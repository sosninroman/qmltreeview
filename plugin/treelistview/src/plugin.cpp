#include "plugin.h"

#include <QtQml/QtQml>

#include "treemodel.h"
#include "selector.h"

void Plugin::registerTypes(const char* uri) {
    qmlRegisterUncreatableType<QmlTreeModelInterface>(uri, 1, 0, "QmlTreeModelInterface", "uncreatable type!");
    qRegisterMetaType<QmlTreeModelInterface*>("QmlTreeModelInterface");

    qmlRegisterType<Selector>(uri, 1, 0, "Selector");
    qRegisterMetaType<Selector*>("Selector");
}
