#ifndef FIXEDSIZETREE_H
#define FIXEDSIZETREE_H

#include <QString>
#include "src/treenode.h"
#include "src/treemodel.h"

class SimpleTreeNode : public TreeNode
{
    using BaseClass = TreeNode;
public:
    explicit SimpleTreeNode(const QString& name): m_name(name)
    {}

    QString name() const {return m_name;}
    void setName(const QString& val) {m_name = val;}

private:
    QString m_name;
};

class FixedSizeTreeModel : public TreeModel<SimpleTreeNode>
{
    Q_OBJECT
    using BaseClass = TreeModel<SimpleTreeNode>;
    using NodeType = SimpleTreeNode;

    enum ProjectTreeRoles
    {
        NameRole = ExtraRole
    };

public:
    explicit FixedSizeTreeModel(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles = BaseClass::roleNames();
        roles.insert(QHash<int, QByteArray>{
            {NameRole, QByteArrayLiteral("name")}
        });
        return roles;
    }

    QVariant data(const QModelIndex& index, int role) const override
    {
        if( !index.isValid() )
        {
            return QVariant();
        }

        NodeType* node = static_cast<NodeType*>( index.internalPointer() );

        switch(role)
        {
        case NameRole:
            return node->name();
        default:
            return BaseClass::data(index, role);
        }
        Q_UNREACHABLE();
    }
};

#endif
