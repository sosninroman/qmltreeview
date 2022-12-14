#ifndef EDITABLESTRINGSTREE_H
#define EDITABLESTRINGSTREE_H

#include <QString>
#include "src/treenode.h"
#include "src/treemodel.h"

namespace tvexample
{

class StringTreeNode : public treeview::TreeNode
{
    using BaseClass = TreeNode;
public:
    explicit StringTreeNode(const QString& name): m_name(name)
    {}

    QString name() const {return m_name;}
    void setName(const QString& val) {m_name = val;}

private:
    QString m_name;
};

class EditableStringsTreeModel : public treeview::TreeModel
{
    Q_OBJECT
    using BaseClass = treeview::TreeModel;
    using NodeType = StringTreeNode;

    enum TreeRoles
    {
        NameRole = treeview::ExtraRole
    };

public:
    explicit EditableStringsTreeModel(QObject* parent = nullptr);

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

    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        if(role == NameRole)
        {
            NodeType* node = static_cast<NodeType*>( index.internalPointer() );
            node->setName(value.toString());
            emit dataChanged(index, index, {NameRole});
            return true;
        }
        return BaseClass::setData(index, value, role);
    }

    Q_INVOKABLE void addChild(const QVariant& index, const QString& name);
    Q_INVOKABLE void moveNode(const QVariant& parentIndexV, const QVariant& indexV);
    Q_INVOKABLE void removeNode(const QVariant& index);
};

}

#endif
