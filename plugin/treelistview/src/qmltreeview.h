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

    Q_PROPERTY(int _maxRowContentWidth READ maxRowContentWidth WRITE setMaxRowContentWidth NOTIFY maxRowContentWidthChanged)
    int maxRowContentWidth() const {return m_maxRowContentWidth;}
    void setMaxRowContentWidth(int val);

    Q_PROPERTY(QVariant _maxWidthRowIndex READ maxWidthRowIndex WRITE setMaxWidthRowIndex NOTIFY maxWidthRowIndexChanged)
    QVariant maxWidthRowIndex() const {return m_maxWidthRowIndex;}
    void setMaxWidthRowIndex(const QVariant& val);

    Q_PROPERTY(int rowContentMargin READ rowContentMargin WRITE setRowContentMargin NOTIFY rowContentMarginChanged)
    int rowContentMargin() const {return m_rowContentMargin;}
    void setRowContentMargin(int val);

    Q_PROPERTY(QVariant rootIndex READ rootIndex NOTIFY modelChanged)
    QVariant rootIndex() const {return m_model ? m_model->rootIndex() : QVariant();}

    Q_PROPERTY(QString test READ test WRITE setTest NOTIFY testChanged)
    QString m_test;
    QString test() const {return m_test;}
    void setTest(const QString& val){if(m_test != val) {m_test = val; emit testChanged();};}
signals:
    void testChanged();

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
    void rowContentMarginChanged();

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
    QmlTreeModelInterface* m_model = nullptr;
    QQmlComponent* m_rowContentDelegate = nullptr;
    QQmlComponent* m_backgroundDelegate = nullptr;
    QQmlComponent* m_dragDelegate = nullptr;
    QQmlComponent* m_expanderDelegate = nullptr;
    int m_maxRowContentWidth = 0;
    QModelIndex m_maxWidthRowIndex;
    int m_rowContentMargin = 0;
    bool m_needToRecalcMaxWidthAfterNextRowRemove = false;
};

#endif
