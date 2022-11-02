#include "rowproperties.h"

RowProperties::RowProperties(QObject *parent):
    QObject(parent)
{}

void RowProperties::initialize(QmlTreeView* view, QVariant parentIndex, int row)
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
    connect(m_view, &QmlTreeView::nodeDataChanged, this, &RowProperties::onNodeDataChanged);
    connect(m_view, &QmlTreeView::nodeChildrenCountChanged, this, &RowProperties::onNodeChildrenCountChanged);

    m_parentIndex = parentIndex.toModelIndex();
    Q_ASSERT(m_view->model());
    m_currentIndex = m_view->model()->index(row, 0, m_parentIndex);
    m_modelData = m_view->model()->nodeData(m_currentIndex);

    emit changed();
    emit modelDataChanged();
    emit childrenCountChanged();
}

int RowProperties::childrenCount() const
{
    return m_view ? m_view->model()->rowCount(m_currentIndex) : 0;
}

void RowProperties::onNodeDataChanged(const QModelIndex& index)
{
    if(m_currentIndex == index)
    {
        m_modelData = m_view->model()->nodeData(m_currentIndex);
        emit modelDataChanged();
    }
}

void RowProperties::onNodeChildrenCountChanged(const QModelIndex& index)
{
    if(m_currentIndex == index)
    {
        m_modelData = m_view->model()->nodeData(m_currentIndex);
        emit childrenCountChanged();
        emit modelDataChanged();
    }
}

void RowProperties::checkMaxWidth(int contentWidth) {
    if(contentWidth > m_view->maxRowContentWidth())
    {
        m_view->setMaxRowContentWidth(contentWidth);
        m_view->setMaxWidthRowIndex(m_currentIndex);
    }
}
