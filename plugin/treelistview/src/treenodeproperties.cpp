#include "treenodeproperties.h"

TreeNodeProperties::TreeNodeProperties(QObject *parent):
    QObject(parent)
{}

void TreeNodeProperties::setRow(int val)
{
    if(m_row != val)
    {
        m_row = val;
        emit rowChanged();
    }
}

void TreeNodeProperties::setParentIndex(const QVariant &val)
{
    QModelIndex ind = val.toModelIndex();
    if(m_parentIndex != ind)
    {
        m_parentIndex = ind;
        emit parentIndexChanged();
    }
}

void TreeNodeProperties::setCurrentIndex(const QVariant &val)
{
    QModelIndex ind = val.toModelIndex();
    if(m_currentIndex != ind)
    {
        m_currentIndex = ind;
        emit currentIndexChanged();
    }
}

void TreeNodeProperties::setView(QmlTreeView* val)
{
    if(m_view != val)
    {
        m_view = val;
        emit viewChanged();
    }
}

void TreeNodeProperties::setSelector(Selector* val)
{
    if(m_selector != val)
    {
        m_selector = val;
        emit selectorChanged();
    }
}

void TreeNodeProperties::setChildCount(int val)
{
    if(m_childCount != val)
    {
        m_childCount = val;
        emit childCountChanged();
    }
}

void TreeNodeProperties::setModelData(const QVariant& val)
{
    if(m_modelData != val)
    {
        m_modelData = val;
        emit modelDataChanged();
    }
}

void TreeNodeProperties::setContentWidth(int val)
{
    if(m_contentWidth != val)
    {
        m_contentWidth = val;
        emit contentWidthChanged();
    }
}
