#ifndef QMLTREEVIEW_H
#define QMLTREEVIEW_H

#include <QObject>
#include <QQuickItem>
#include <QQmlComponent>
#include "selector.h"
#include "treemodel.h"

namespace treeview
{

class TREE_VIEW_API QmlTreeView : public QQuickItem
{
    Q_OBJECT
public:
    explicit QmlTreeView(QQuickItem *parent = nullptr);

    Q_PROPERTY(treeview::Selector* selector READ selector CONSTANT)
    Selector* selector() {return &m_selector;}

    Q_PROPERTY(QmlTreeModel* model READ model WRITE setModel NOTIFY modelChanged)
    QmlTreeModel* model() {return m_model;}
    void setModel(QmlTreeModel* model);

    Q_PROPERTY(QModelIndex rootIndex READ rootIndex NOTIFY modelChanged)
    QModelIndex rootIndex() const {return m_model ? m_model->rootIndex() : QModelIndex();}

    Q_PROPERTY(QQmlComponent* rowContentDelegate READ rowContentDelegate WRITE setRowContentDelegate NOTIFY rowContentDelegateChanged)
    QQmlComponent* rowContentDelegate() const {return m_rowContentDelegate;}
    void setRowContentDelegate(QQmlComponent* val);

    Q_PROPERTY(QQmlComponent* backgroundDelegate READ backgroundDelegate WRITE setBackgroundDelegate NOTIFY backgroundDelegateChanged)
    QQmlComponent* backgroundDelegate() const {return m_backgroundDelegate;}
    void setBackgroundDelegate(QQmlComponent* val);

    Q_PROPERTY(QQmlComponent* dragDelegate READ dragDelegate WRITE setDragDelegate NOTIFY dragDelegateChanged)
    QQmlComponent* dragDelegate() const {return m_dragDelegate;}
    void setDragDelegate(QQmlComponent* val);

    Q_PROPERTY(QQmlComponent* expanderDelegate READ expanderDelegate WRITE setExpanderDelegate NOTIFY expanderDelegateChanged)
    QQmlComponent* expanderDelegate() const {return m_expanderDelegate;}
    void setExpanderDelegate(QQmlComponent* val);

    Q_PROPERTY(QQmlComponent* scrollBarDelegate READ scrollBarDelegate WRITE setScrollBarDelegate NOTIFY scrollBarDelegateChanged)
    QQmlComponent* scrollBarDelegate() const {return m_scrollBarDelegate;}
    void setScrollBarDelegate(QQmlComponent* val);

    Q_PROPERTY(int scrollVelocity READ scrollVelocity WRITE setScrollVelocity NOTIFY scrollVelocityChanged)
    int scrollVelocity() const {return m_scrollVelocity;}
    void setScrollVelocity(int val);

    Q_PROPERTY(int availableWidth READ availableWidth WRITE setAvailableWidth NOTIFY availableWidthChanged)
    int availableWidth() const {return m_availableWidth;}
    void setAvailableWidth(int val);

    Q_PROPERTY(int _maxRowContentWidth READ maxRowContentWidth WRITE setMaxRowContentWidth NOTIFY maxRowContentWidthChanged)
    int maxRowContentWidth() const {return m_maxRowContentWidth;}
    void setMaxRowContentWidth(int val);

    Q_PROPERTY(QModelIndex _maxWidthRowIndex READ maxWidthRowIndex WRITE setMaxWidthRowIndex NOTIFY maxWidthRowIndexChanged)
    QModelIndex maxWidthRowIndex() const {return m_maxWidthRowIndex;}
    void setMaxWidthRowIndex(const QModelIndex& val);

public slots:
    Q_INVOKABLE void recalcMaxRowWidth();

signals:
    void canceled();
    void clicked(QVariant mouse);
    void doubleClicked(QVariant mouse);
    void entered();
    void exited();
    void positionChanged(QVariant mouse);
    void pressAndHold(QVariant mouse);
    void pressed(QVariant mouse);
    void released(QVariant mouse);
    void wheel(QVariant wheel);

    void modelChanged();
    void nodeDataChanged(const QModelIndex&);
    void nodeChildrenCountChanged(const QModelIndex& ind);

    void rowContentDelegateChanged();
    void backgroundDelegateChanged();
    void dragDelegateChanged();
    void expanderDelegateChanged();
    void scrollBarDelegateChanged();

    void availableWidthChanged();
    void scrollVelocityChanged();
    void needToRecalcMaxRowWidth();
    void maxRowContentWidthChanged();
    void maxWidthRowIndexChanged();

private:
    void disconnectFromModel();
    void connectToModel();
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
    void onRowsChildrenCountChanged(const QModelIndex& parent);
    void onNodeChildrenCountChanged(const QModelIndex& ind);
    void onRowsAboutToBeRemoved(const QModelIndex& parent, int first, int last);
    void onRowsRemoved(const QModelIndex& parent, int first, int last);

private:
    Selector m_selector;
    QmlTreeModel* m_model = nullptr;
    QQmlComponent* m_rowContentDelegate = nullptr;
    QQmlComponent* m_backgroundDelegate = nullptr;
    QQmlComponent* m_dragDelegate = nullptr;
    QQmlComponent* m_expanderDelegate = nullptr;
    QQmlComponent* m_scrollBarDelegate = nullptr;
    int m_maxRowContentWidth = 0;
    QModelIndex m_maxWidthRowIndex;
    bool m_needToRecalcMaxWidthAfterNextRowRemove = false;
    int m_availableWidth = 0;
    int m_scrollVelocity = 1;
};

}

#endif
