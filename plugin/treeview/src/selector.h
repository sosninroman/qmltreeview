#ifndef SELECTOR_H
#define SELECTOR_H

#include "export.h"
#include <QObject>
#include <QModelIndex>
#include <QModelIndexList>

namespace treeview
{

/*!
 * \brief This class contains selection state the tree.
 * Selector is used inside row delegates in order to control selection
 * behavior and tune delegates styles.
 */
class TREE_VIEW_API Selector: public QObject
{
    Q_OBJECT

public:
    explicit Selector(QObject* parent = nullptr): QObject(parent) {}

    Q_PROPERTY(QModelIndex currentIndex READ currentIndex NOTIFY currentChanged)
    /*!
     * \brief Return current index of the view.
     * The current index can be used to store the index of the row with the mouse cursor.
     */
    QModelIndex currentIndex() const {return m_currentIndex;}

    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY selectionChanged)
    /*!
     * \brief Return true if selector contains any selected indexes.
     */
    bool hasSelection() const {return !m_selectedIndexes.isEmpty();}

    Q_PROPERTY(QModelIndexList selectedIndexes READ selectedIndexes NOTIFY selectionChanged)
    /*!
     * \brief Return a list of selected indexes.
     */
    QModelIndexList selectedIndexes() const {return m_selectedIndexes;}

signals:
    void currentChanged(QModelIndex current, QModelIndex previous);
    void selectionChanged();

public slots:
    /*!
     * \brief Clear selection state.
     */
    void clear();
    /*!
     * \brief Clear current index.
     */
    void clearCurrentIndex();
    /*!
     * \brief Clear the list of selected indexes.
     */
    void clearSelection();
    /*!
     * \brief Return true if a specific index is selected.
     */
    bool isSelected(QModelIndex index);
    /*!
     * \brief Add a specific index to the list of selected indexes.
     */
    void select(QModelIndex index);
    /*!
     * \brief Update the current view index.
     */
    void setCurrentIndex(QModelIndex index);

private:
    QModelIndex m_currentIndex;
    QModelIndexList m_selectedIndexes;
};

}

#endif
