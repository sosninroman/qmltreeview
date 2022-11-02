#ifndef SELECTOR_H
#define SELECTOR_H

#include <QObject>
#include <QModelIndex>
#include <QModelIndexList>

namespace treeview
{

class Selector: public QObject
{
    Q_OBJECT
    using BaseClass = QObject;

public:
    explicit Selector(QObject* parent = nullptr): BaseClass(parent) {}

    Q_PROPERTY(QModelIndex currentIndex READ currentIndex NOTIFY currentChanged)
    QModelIndex currentIndex() const {return m_currentIndex;}

    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY selectionChanged)
    bool hasSelection() const {return !m_selectedIndexes.isEmpty();}

    Q_PROPERTY(QModelIndexList selectedIndexes READ selectedIndexes NOTIFY selectionChanged)
    QModelIndexList selectedIndexes() const {return m_selectedIndexes;}

signals:
    void currentChanged(QModelIndex current, QModelIndex previous);
    void selectionChanged();

public slots:
    void clear();
    void clearCurrentIndex();
    void clearSelection();
    bool isSelected(QModelIndex index);
    void select(QModelIndex index);
    void setCurrentIndex(QModelIndex index);

private:
    QModelIndex m_currentIndex;
    QModelIndexList m_selectedIndexes;
};

}

#endif
