#ifndef ROWPROPERIES_H
#define ROWPROPERIES_H

#include <QObject>
#include <QQuickItem>
#include <QQmlComponent>
#include <QModelIndex>
#include "treeviewitem.h"

namespace treeview
{

/*!
 * \brief This class represents all data available inside row delegates.
 * RowProperties can be used in delegates to set and get information
 * about current model data, selection state and view properties.
 */
class TREE_VIEW_API RowProperties : public QObject
{
    Q_OBJECT
public:
    explicit RowProperties(QObject* parent = nullptr);

    Q_PROPERTY(QVariant parentIndex READ parentIndex NOTIFY changed)
    QVariant parentIndex() const {return m_parentIndex;}

    Q_PROPERTY(QVariant index READ index NOTIFY changed)
    QVariant index() const {return m_index;}

    Q_PROPERTY(treeview::TreeViewItem* view READ view NOTIFY changed)
    TreeViewItem* view() const {return m_view;}

    Q_PROPERTY(treeview::Selector* selector READ selector NOTIFY changed)
    Selector* selector() const  {return m_view ? m_view->selector() : nullptr;}

    Q_PROPERTY(int childrenCount READ childrenCount NOTIFY childrenCountChanged)
    int childrenCount() const;

    Q_PROPERTY(QVariant modelData READ modelData NOTIFY modelDataChanged)
    QVariant modelData() const {return m_modelData;}

    Q_INVOKABLE void initialize(TreeViewItem* view, QVariant parentIndex, int row);
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
    QModelIndex m_index;
    TreeViewItem* m_view = nullptr;
    QVariant m_modelData;
};

}

#endif
