#ifndef TREEHELPER_H
#define TREEHELPER_H

#include <QObject>
#include <QtQml/qqml.h>
#include "export.h"
#include <QModelIndex>

class TREE_LIST_VIEW_API TreeHelper : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
public:

    static QObject* instance(QQmlEngine *engine,  QJSEngine *scriptEngine);

    Q_INVOKABLE bool checkNodeBetween(QVariant index, QVariant lIndex, QVariant rIndex);

private:
    static TreeHelper* m_instance;
};

#endif
