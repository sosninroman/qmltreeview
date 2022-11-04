#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "treenode.h"
#include <QQmlPropertyMap>
#include <QDebug>
#include "export.h"
#include "qmltreemodel.h"

namespace treeview
{

template<class NodeType>
class TreeModel : public QmlTreeModel
{
    using BaseClass = QmlTreeModel;

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
            return createIndex(row, column, m_root->children().at(row));
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
            return m_root->childrenCount();
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
    }


    bool hasChildren(const QModelIndex& parentIndex) const override
    {
        if (!parentIndex.isValid())
            return m_root->hasChildren();
        return static_cast<NodeType*>(parentIndex.internalPointer())->hasChildren();
    }

//    void clear() final
//    {
//        BaseClass::clear();
//    }
};

}

#endif
