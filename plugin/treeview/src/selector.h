#ifndef SELECTOR_H
#define SELECTOR_H

#include "export.h"
#include <QObject>
#include <QModelIndex>
#include <QModelIndexList>

namespace treeview
{

/*!
 * \brief This class contains selection of tree view.
 * Selector is used inside row delegates in order to control selection
 * behavior and tune delegates styles.
 */
class TREE_VIEW_API Selector: public QObject
{
    Q_OBJECT
    using BaseClass = QObject;

public:
    explicit Selector(QObject* parent = nullptr): BaseClass(parent) {}

    Q_PROPERTY(QModelIndex currentIndex READ currentIndex NOTIFY currentChanged)
    /*!
     * \brief Return current index of the view.
     * Current index could be used for containing an index of row with mouse cursor.
     */
    QModelIndex currentIndex() const {return m_currentIndex;}

    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY selectionChanged)
    /*!
     * \brief Return true if selector contains any selected indexes.
     */
    bool hasSelection() const {return !m_selectedIndexes.isEmpty();}

    Q_PROPERTY(QModelIndexList selectedIndexes READ selectedIndexes NOTIFY selectionChanged)
    /*!
     * \brief Return a list of selected indexes
     */
    QModelIndexList selectedIndexes() const {return m_selectedIndexes;}

signals:
    void currentChanged(QModelIndex current, QModelIndex previous);
    void selectionChanged();

public slots:
    /*!
     * \brief Clear selection and current index
     */
    void clear();
    /*!
     * \brief Clear current index
     */
    void clearCurrentIndex();
    /*!
     * \brief Clear the list of selected indexes
     */
    void clearSelection();
    /*!
     * \brief Return true if particular index is selected
     */
    bool isSelected(QModelIndex index);
    /*!
     * \brief Put particular index into selected indexes list
     */
    void select(QModelIndex index);
    /*!
     * \brief Update current index
     */
    void setCurrentIndex(QModelIndex index);

private:
    QModelIndex m_currentIndex;
    QModelIndexList m_selectedIndexes;
};

}

#endif
