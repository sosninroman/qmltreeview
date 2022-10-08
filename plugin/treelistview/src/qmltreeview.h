#ifndef QMLTREEVIEW_H
#define QMLTREEVIEW_H

#include <QObject>
#include <QQuickItem>
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
    void nodeChildrenCountChanged(const QModelIndex&);

private:
    void disconnectFromModel();
    void connectToModel();
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
    void onRowsInserted(const QModelIndex& index);

private:
    Selector m_selector;
    QmlTreeModelInterface* m_model = nullptr;
};

#endif
