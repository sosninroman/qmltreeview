#include "treenodeproperties.h"

TreeNodeProperties::TreeNodeProperties(QObject *parent):
    QObject(parent)
{}

//void TreeNodeProperties::setRow(int val)
//{
//    if(m_row != val)
//    {
//        m_row = val;
//        emit rowChanged();
//    }
//}

void TreeNodeProperties::setParentIndex(const QVariant &val)
{
    Q_UNUSED(val);
//    QModelIndex ind = val.toModelIndex();
//    if(m_parentIndex != ind)
//    {
//        m_parentIndex = ind;
//        emit parentIndexChanged();
//    }
}

void TreeNodeProperties::setCurrentIndex(const QVariant &val)
{
    Q_UNUSED(val);
//    QModelIndex ind = val.toModelIndex();
//    if(m_currentIndex != ind)
//    {
//        m_currentIndex = ind;
//        emit currentIndexChanged();
//    }
}

void TreeNodeProperties::setView(QmlTreeView* val)
{
    Q_UNUSED(val);
//    if(m_view != val)
//    {
//        m_view = val;
//        emit viewChanged();
//    }
}

void TreeNodeProperties::setChildCount(int val)
{
    Q_UNUSED(val);
//    if(m_childCount != val)
//    {
//        m_childCount = val;
//        emit childCountChanged();
//    }
}

void TreeNodeProperties::setModelData(const QVariant& val)
{
    Q_UNUSED(val);
//    if(m_modelData != val)
//    {
//        m_modelData = val;
//        emit modelDataChanged();
//    }
}

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

//void TreeNodeProperties::init(const TreeNodeProperties& parentProperties, int row)
//{
//    qCritical() << "ola" << parentProperties.view()->test();
//    setRow(row);
//    setParentIndex(parentProperties.currentIndex());
//    m_view = parentProperties.view();
//    setView(parentProperties.view());
//}
