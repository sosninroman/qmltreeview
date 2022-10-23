#include "treenodeproperties.h"

TreeNodeProperties::TreeNodeProperties(QObject *parent):
    QObject(parent)
{}

void TreeNodeProperties::initialize(QmlTreeView* view, QVariant parentIndex, int row)
{
    if(!view)
    {
        return;
    }

    if(m_view)
    {
        disconnect(m_view);
    }
    m_view = view;
    connect(m_view, &QmlTreeView::nodeDataChanged, this, &TreeNodeProperties::onNodeDataChanged);
    connect(m_view, &QmlTreeView::nodeChildrenCountChanged, this, &TreeNodeProperties::onNodeChildrenCountChanged);

    m_parentIndex = parentIndex.toModelIndex();
    Q_ASSERT(view->model());
    m_currentIndex = view->model()->index(row, 0, m_parentIndex);

    m_childCount = view->model()->rowCount(m_currentIndex);
    m_modelData = view->model()->nodeData(m_currentIndex);

    emit changed();
    emit modelDataChanged();
    emit childrenCountChanged();
}

void TreeNodeProperties::onNodeDataChanged(const QModelIndex& index)
{
    if(m_currentIndex == index)
    {
        m_modelData = m_view->model()->nodeData(m_currentIndex);
        emit modelDataChanged();
    }
}

void TreeNodeProperties::onNodeChildrenCountChanged(const QModelIndex& index)
{
    if(m_currentIndex == index)
    {
        m_modelData = m_view->model()->nodeData(m_currentIndex);
        m_childCount = m_view->model()->rowCount(m_currentIndex);
        emit childrenCountChanged();
        emit modelDataChanged();
    }
}
