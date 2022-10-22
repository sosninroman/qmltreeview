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
    connect(this, &QmlTreeView::nodeChildrenCountChanged, this, &QmlTreeView::onNodeChildrenCountChanged);
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
    connect(m_model, &QAbstractItemModel::rowsInserted, this, &QmlTreeView::onRowsChildrenCountChanged);
    connect(m_model, &QAbstractItemModel::rowsRemoved, this, &QmlTreeView::onRowsChildrenCountChanged);
    connect(m_model, &QAbstractItemModel::rowsMoved, this, [this](const QModelIndex& from, int, int, const QModelIndex& to){
        qCritical() << from << to << "\n";
        onRowsChildrenCountChanged(from);
        onRowsChildrenCountChanged(to);
    });
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

void QmlTreeView::onRowsChildrenCountChanged(const QModelIndex& parent)
{
    if(parent.isValid())
    {
        emit nodeChildrenCountChanged(parent);
    }
}

void QmlTreeView::onNodeChildrenCountChanged(const QModelIndex& ind)
{
    if(m_model && ind == m_model->rootIndex()) {
        m_model->refresh();
    }
}

void QmlTreeView::setRowContentDelegate(QQmlComponent* val)
{
    if(m_rowContentDelegate != val)
    {
        m_rowContentDelegate = val;
        emit rowContentDelegateChanged();
    }
}

void QmlTreeView::setBackgroundDelegate(QQmlComponent* val)
{
    if(m_backgroundDelegate != val)
    {
        m_backgroundDelegate = val;
        emit backgroundDelegateChanged();
    }
}

void QmlTreeView::setDragDelegate(QQmlComponent* val)
{
    if(m_dragDelegate != val)
    {
        m_dragDelegate = val;
        emit dragDelegateChanged();
    }
}

void QmlTreeView::setExpanderDelegate(QQmlComponent* val)
{
    if(m_expanderDelegate != val)
    {
        m_expanderDelegate = val;
        emit expanderDelegateChanged();
    }
}

void QmlTreeView::setMaxRowContentWidth(int val)
{
    if(m_maxRowContentWidth != val)
    {
        m_maxRowContentWidth = val;
        emit maxRowContentWidthChanged();
    }
}


void QmlTreeView::setMaxWidthRowIndex(const QVariant &val)
{
    QModelIndex ind = val.toModelIndex();
    if(m_maxWidthRowIndex != ind)
    {
        m_maxWidthRowIndex = ind;
        emit maxWidthRowIndexChanged();
    }
}

void QmlTreeView::setRowContentMargin(int val)
{
    if(m_rowContentMargin != val)
    {
        m_rowContentMargin = val;
        emit rowContentMarginChanged();
    }
}

void QmlTreeView::recalcMaxRowWidth()
{
    setMaxRowContentWidth(0);
    setMaxWidthRowIndex(QModelIndex());
    emit needToRecalcMaxRowWidth();
}
