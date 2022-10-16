#ifndef QMLTREEVIEW_H
#define QMLTREEVIEW_H

#include <QObject>
#include <QQuickItem>
#include <QQmlComponent>
#include "selector.h"
#include "treemodel.h"

class QmlTreeView : public QQuickItem
{
    Q_OBJECT
public:
    explicit QmlTreeView(QQuickItem *parent = nullptr);

    Q_PROPERTY(Selector* selector READ selector CONSTANT)
    Selector* selector() {return &m_selector;}

    Q_PROPERTY(QmlTreeModelInterface* model READ model WRITE setModel NOTIFY modelChanged)
    QmlTreeModelInterface* model() {return m_model;}
    void setModel(QmlTreeModelInterface* model);

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

private:
    void disconnectFromModel();
    void connectToModel();
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
    void onRowsChildrenCountChanged(const QModelIndex& parent);

private:
    Selector m_selector;
    QmlTreeModelInterface* m_model = nullptr;
    QQmlComponent* m_rowContentDelegate = nullptr;
    QQmlComponent* m_backgroundDelegate = nullptr;
    QQmlComponent* m_dragDelegate = nullptr;
    QQmlComponent* m_expanderDelegate = nullptr;
};

#endif
