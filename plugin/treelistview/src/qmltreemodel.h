#ifndef QMLTREEMODEL_H
#define QMLTREEMODEL_H

#include <memory>
#include <QAbstractItemModel>
#include "export.h"
#include "treenode.h"

namespace treeview
{

class TreeNode;

enum TreeModelRoles
{
    ExpandedRole = Qt::UserRole,
    ExpandableRole,
    NodeLevelRole,
    NodeIdRole,
    IndexRole,

    ExtraRole
};

class TREE_LIST_VIEW_API QmlTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    using BaseClass = QAbstractItemModel;

    class RootNode : public TreeNode
    {
    public:
        void appendChild(TreeNode *node) final {
            node->setParent(this);
            m_children.append(node);
        }
    };

public:
    explicit QmlTreeModel(QObject* parent = nullptr);

    Q_INVOKABLE QModelIndex rootIndex();

    Q_INVOKABLE QVariant nodeData(const QModelIndex& index);

    Q_INVOKABLE void refresh();

    virtual void clear();

    using QAbstractItemModel::index;

    QModelIndex index(TreeNode* node);

signals:
    void busyChanged();

protected:
    std::unique_ptr<RootNode> m_root;
};

}

#endif
