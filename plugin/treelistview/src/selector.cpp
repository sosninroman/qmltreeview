#include "selector.h"

namespace treeview
{

void Selector::clear()
{
    clearCurrentIndex();
    clearSelection();
}

void Selector::clearCurrentIndex()
{
    if( m_currentIndex.isValid() )
    {
        setCurrentIndex( QModelIndex() );
    }
}

void Selector::clearSelection()
{
    if( !m_selectedIndexes.isEmpty() )
    {
        m_selectedIndexes.clear();
        emit selectionChanged();
    }
}

bool Selector::isSelected(QModelIndex index)
{
    return std::find(m_selectedIndexes.cbegin(), m_selectedIndexes.cend(), index) != m_selectedIndexes.cend();
}

void Selector::select(QModelIndex index)
{
    if( !isSelected(index) )
    {
        m_selectedIndexes.append(index);
        emit selectionChanged();
    }
}

void Selector::setCurrentIndex(QModelIndex index)
{
    if(m_currentIndex != index)
    {
        const auto oldInd = m_currentIndex;
        m_currentIndex = index;
        emit currentChanged(m_currentIndex, oldInd);
    }
}

}
