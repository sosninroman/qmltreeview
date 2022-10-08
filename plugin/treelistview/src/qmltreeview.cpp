#include "qmltreeview.h"
#include <stack>

namespace
{

TreeNode* nextNode(TreeNode* node)
{
    while(node && node->parent())
    {
        const auto pos = node->row();
        const auto parent = node->parent();
        Q_ASSERT(parent);
        if(pos < parent->childrenCount() - 1)
        {
            return parent->children().at(pos + 1);
        }
        else
        {
            node = parent;
        }
    }
    return nullptr;
}

}

QmlTreeView::QmlTreeView(QQuickItem *parent):
    QQuickItem(parent)
{

}

void QmlTreeView::setModel(QmlTreeModelInterface* model)
{
    if(m_model != model)
    {
        disconnectFromModel();
        m_model = model;
        connectToModel();
        emit modelChanged();
    }
}

void QmlTreeView::disconnectFromModel()
{
    if(!m_model)
    {
        return;
    }
    disconnect(m_model);
}

void QmlTreeView::connectToModel()
{
    if(!m_model)
    {
        return;
    }
    connect(m_model, &QAbstractItemModel::dataChanged, this, &QmlTreeView::onDataChanged);
    connect(m_model, &QAbstractItemModel::rowsInserted, this, &QmlTreeView::onRowsInserted);
}

void QmlTreeView::onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    if(!topLeft.isValid())
    {
        return;
    }
    emit nodeDataChanged(topLeft);
    TreeNode* node = static_cast<TreeNode*>(topLeft.internalPointer());
    Q_ASSERT(node);
    while(node)
    {
        node = nextNode(node);
        if(node)
        {
            const auto index = m_model->index(node);
            if(index == bottomRight)
            {
                return;
            }
            emit nodeDataChanged(index);
        }
    }
}

void QmlTreeView::onRowsInserted(const QModelIndex& index)
{
    if(index.isValid())
    {
        emit nodeChildrenCountChanged(index);
    }
}
