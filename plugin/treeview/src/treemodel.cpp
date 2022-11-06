#include "treemodel.h"
#include <QQmlPropertyMap>

namespace treeview
{

TreeModel::TreeModel(QObject* parent) :
    BaseClass(parent), m_root( new RootNode() )
{}

QModelIndex TreeModel::rootIndex()
{
    return createIndex( 0, 0, m_root.get() );
}

QVariant TreeModel::nodeData(const QModelIndex& index)
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
        this->setData( index, val, rolesByName.value(roleName) );
    });
    return QVariant::fromValue(result);
}

QModelIndex TreeModel::index(TreeNode* node)
{
    if(!node)
    {
        return QModelIndex();
    }
    return createIndex(node->row(), 0, node);
}

void TreeModel::addTopLevelNode(TreeNode* node)
{
    m_root->appendChild(node);
}

void TreeModel::reset()
{
    beginResetModel();
    endResetModel();
}

QHash<int, QByteArray> TreeModel::roleNames() const
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

int TreeModel::columnCount(const QModelIndex&) const
{
    return 1;
}

bool TreeModel::hasChildren(const QModelIndex& parentIndex) const
{
    if (!parentIndex.isValid())
        return m_root->hasChildren();
    return static_cast<TreeNode*>(parentIndex.internalPointer())->hasChildren();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if(row < 0)
    {
        return QModelIndex();
    }
    if(!parent.isValid())
    {
        return createIndex(row, column, m_root->children().at(row));
    }
    const auto node = static_cast<TreeNode*>(parent.internalPointer());
    Q_ASSERT(node);
    const auto child = node->child(row);
    return child ? createIndex(row, column, child) : QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeNode* child = static_cast<TreeNode*>(index.internalPointer());
    auto parent = child->parent();

    if(!parent)
        return QModelIndex();

    return createIndex(parent->row(), 0, parent);
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    if(!parent.isValid())
    {
        return m_root->childrenCount();
    }

    const auto parentNode = static_cast<TreeNode*>(parent.internalPointer());

    return parentNode->childrenCount();
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    TreeNode* node = static_cast<TreeNode*>(index.internalPointer());

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

bool TreeModel::setData(const QModelIndex& index, const QVariant &value, int role)
{
    if(!index.isValid())
    {
        return false;
    }

    TreeNode* node = static_cast<TreeNode*>(index.internalPointer());
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

}
