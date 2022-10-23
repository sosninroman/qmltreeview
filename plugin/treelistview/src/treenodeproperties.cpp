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
    Q_ASSERT(m_view->model());
    m_currentIndex = m_view->model()->index(row, 0, m_parentIndex);
    m_modelData = m_view->model()->nodeData(m_currentIndex);

    emit changed();
    emit modelDataChanged();
    emit childrenCountChanged();
}

int TreeNodeProperties::childrenCount() const
{
    return m_view ? m_view->model()->rowCount(m_currentIndex) : 0;
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
        emit childrenCountChanged();
        emit modelDataChanged();
    }
}

void TreeNodeProperties::checkMaxWidth(int contentWidth) {
    if(contentWidth > m_view->maxRowContentWidth())
    {
        m_view->setMaxRowContentWidth(contentWidth);
        m_view->setMaxWidthRowIndex(m_currentIndex);
    }
}
