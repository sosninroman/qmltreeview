#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "treenode.h"
#include <QQmlPropertyMap>
#include <QDebug>
#include "export.h"

class TREE_LIST_VIEW_API QmlTreeModelInterface : public QAbstractItemModel
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
    explicit QmlTreeModelInterface(QObject* parent = nullptr) :
          BaseClass(parent), m_root( new RootNode() ) {}

    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    bool busy() const {return m_busy;}
    void setBusy(bool val) {m_busy = val;}

    Q_INVOKABLE QModelIndex rootIndex()
    {
        return createIndex( 0, 0, m_root.get() );
    }

    Q_INVOKABLE QVariant nodeData(const QModelIndex& index)
    {
        const auto result = new QQmlPropertyMap(this);
        const auto roles = roleNames();
        QHash<QString, int> rolesByName;
        for(auto roleItr = roles.cbegin(); roleItr != roles.end(); ++roleItr)
        {
            rolesByName.insert( roleItr.value(), roleItr.key() );
            result->insert(roleItr.value(), data( index, roleItr.key() ) );
        }

        connect(result, &QQmlPropertyMap::valueChanged, this, [rolesByName, this, index](const QString& roleName, const QVariant& val){
            this->setData( index, rolesByName.value(roleName) );
        });
        return QVariant::fromValue(result);
    }

    virtual void clear()
    {
        m_root->clearChildren();
    }

signals:
    void busyChanged();
    void countChanged(const QModelIndex& index);

protected:
    std::unique_ptr<RootNode> m_root;

private:
    bool m_busy = false;
};

enum TreeModelRoles
{
    ExpandedRole = Qt::UserRole,
    ExpandableRole,
    NodeLevelRole,
    NodeIdRole,
    IndexRole,

    ExtraRole
};

template<class NodeType>
class TreeModel : public QmlTreeModelInterface
{
    using BaseClass = QmlTreeModelInterface;    

public:
    explicit TreeModel(QObject* parent = nullptr) : BaseClass(parent) {}

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles = BaseClass::roleNames();
        roles.insert(QHash<int, QByteArray>{
            {ExpandedRole, QByteArrayLiteral("expanded")},
            {ExpandableRole, QByteArrayLiteral("expandable")},
            {NodeLevelRole, QByteArrayLiteral("nodeLevel")},
            {NodeIdRole, QByteArrayLiteral("nodeId")},
            {IndexRole, QByteArrayLiteral("index")},
        });
        return roles;
    }

    QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const override
    {
        if(row < 0 )
        {
            return QModelIndex();
        }
        if( !parent.isValid() )
        {
            return createIndex(row, column, m_topLevelNodes.at(row));
        }
        const auto node = static_cast<NodeType*>( parent.internalPointer() );
        Q_ASSERT(node);
        const auto child = node->child(row);
        return child ? createIndex(row, column, child) : QModelIndex();
    }

    QModelIndex parent(const QModelIndex &index) const override
    {
        if ( !index.isValid() )
            return QModelIndex();

        NodeType* child = static_cast<NodeType*>( index.internalPointer() );
        auto parent = child->parent();

        if(!parent)
            return QModelIndex();

        return createIndex(parent->row(), 0, parent);
    }

    int rowCount(const QModelIndex& parent) const override
    {
        if( !parent.isValid() )
        {
            return m_topLevelNodes.size();
        }

        const auto parentNode = static_cast<NodeType*>( parent.internalPointer() );

        return parentNode->childrenCount();
    }

    int columnCount(const QModelIndex&) const override
    {
        return 1;
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
        case ExpandedRole:
            return node->expanded();
        case ExpandableRole:
            return node->childrenCount() > 0;
        case NodeLevelRole:
            return node->level();
        case NodeIdRole:
            return reinterpret_cast<quint64>(node);
        case IndexRole:
            return index;
        default:
            return QVariant();
        }
        Q_UNREACHABLE();
    }

    bool setData(const QModelIndex& index, const QVariant &value, int role = Qt::EditRole) override
    {
        if( !index.isValid() )
        {
            return false;
        }

        NodeType* node = static_cast<NodeType*>( index.internalPointer() );
        switch(role)
        {
        case ExpandedRole:
        {
            bool val = value.toBool();
            if(val != node->expanded())
            {
                node->setExpanded(val);
                emit dataChanged(index, index, {ExpandedRole});
            }
        }
        }
        return false;
    }

    void addTopLevelNode(NodeType* node)
    {
        m_root->appendChild(node);
        m_topLevelNodes.push_back(node);
    }

    QVector<NodeType*> topLevelNodes() const
    {
        return m_topLevelNodes;
    }


    bool hasChildren(const QModelIndex& parentIndex) const override
    {
        if (!parentIndex.isValid())
            return !m_topLevelNodes.empty();
        return static_cast<NodeType*>(parentIndex.internalPointer())->hasChildren();
    }

    void clear() final
    {
        BaseClass::clear();
        m_topLevelNodes.clear();
    }

private:
    QVector<NodeType*> m_topLevelNodes;
};

#endif
