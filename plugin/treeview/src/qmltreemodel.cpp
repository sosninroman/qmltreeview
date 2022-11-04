#include "qmltreemodel.h"
#include <QQmlPropertyMap>

namespace treeview
{

QmlTreeModel::QmlTreeModel(QObject* parent) :
    BaseClass(parent), m_root( new RootNode() )
{}

QModelIndex QmlTreeModel::rootIndex()
{
    return createIndex( 0, 0, m_root.get() );
}

QVariant QmlTreeModel::nodeData(const QModelIndex& index)
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

//void QmlTreeModel::refresh()
//{
//    beginResetModel();
//    endResetModel();
//}

void QmlTreeModel::clear()
{
    m_root->clearChildren();
}

QModelIndex QmlTreeModel::index(TreeNode* node)
{
    if(!node)
    {
        return QModelIndex();
    }
    return createIndex(node->row(), 0, node);
}

}
