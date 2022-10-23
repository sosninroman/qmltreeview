#ifndef QMLTREENODE_H
#define QMLTREENODE_H

#include <QObject>
#include <QQuickItem>
#include <QQmlComponent>
#include <QModelIndex>
#include "qmltreeview.h"

class TreeNodeProperties : public QObject
{
    Q_OBJECT
public:
    explicit TreeNodeProperties(QObject* parent = nullptr);

    Q_PROPERTY(QVariant parentIndex READ parentIndex NOTIFY changed)
    QVariant parentIndex() const {return m_parentIndex;}

    Q_PROPERTY(QVariant currentIndex READ currentIndex NOTIFY changed)
    QVariant currentIndex() const {return m_currentIndex;}

    Q_PROPERTY(QmlTreeView* view READ view NOTIFY changed)
    QmlTreeView* view() const {return m_view;}

    Q_PROPERTY(Selector* selector READ selector NOTIFY changed)
    Selector* selector() const  {return m_view ? m_view->selector() : nullptr;}

    Q_PROPERTY(int childrenCount READ childrenCount NOTIFY childrenCountChanged)
    int childrenCount() const;

    Q_PROPERTY(QVariant modelData READ modelData NOTIFY modelDataChanged)
    QVariant modelData() const {return m_modelData;}

    Q_INVOKABLE void initialize(QmlTreeView* view, QVariant parentIndex, int row);
    Q_INVOKABLE void checkMaxWidth(int contentWidth);

signals:
    void changed();
    void modelDataChanged();
    void childrenCountChanged();

private:
    void onNodeDataChanged(const QModelIndex& index);
    void onNodeChildrenCountChanged(const QModelIndex& index);

private:
    QModelIndex m_parentIndex;
    QModelIndex m_currentIndex;
    QmlTreeView* m_view = nullptr;
    QVariant m_modelData;
};

#endif
