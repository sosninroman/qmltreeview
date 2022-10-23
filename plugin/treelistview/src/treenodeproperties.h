#ifndef QMLTREENODE_H
#define QMLTREENODE_H

#include <QObject>
#include <QQuickItem>
#include <QQmlComponent>
#include <QModelIndex>
#include "qmltreeview.h"

class TreeNodeProperties : public QObject
{
    Q_OBJECT
public:
    explicit TreeNodeProperties(QObject *parent = nullptr);

//    Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
//    int row() const {return m_row;}
//    void setRow(int val);

    Q_PROPERTY(QVariant parentIndex READ parentIndex WRITE setParentIndex NOTIFY changed)
    QVariant parentIndex() const {return m_parentIndex;}
    void setParentIndex(const QVariant& val);

    Q_PROPERTY(QVariant currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY changed)
    QVariant currentIndex() const {return m_currentIndex;}
    void setCurrentIndex(const QVariant& val);

    Q_PROPERTY(QmlTreeView* view READ view WRITE setView NOTIFY changed)
    QmlTreeView* view() const {return m_view;}
    void setView(QmlTreeView* val);

    Q_PROPERTY(Selector* selector READ selector NOTIFY changed)
    Selector* selector() const  {return m_view ? m_view->selector() : nullptr;}

    Q_PROPERTY(int childCount READ childCount WRITE setChildCount NOTIFY childrenCountChanged)
    int childCount() const {return m_childCount;}
    void setChildCount(int val);

    Q_PROPERTY(QVariant modelData READ modelData WRITE setModelData NOTIFY modelDataChanged)
    QVariant modelData() const {return m_modelData;}
    void setModelData(const QVariant& val);

    Q_INVOKABLE void initialize(QmlTreeView* view, QVariant parentIndex, int row);
//    Q_INVOKABLE void init(const TreeNodeProperties& parentProperties, int row);

signals:
    void changed();
    void modelDataChanged();
    void childrenCountChanged();

//    void rowChanged();
//    void viewChanged();
//    void parentIndexChanged();
//    void currentIndexChanged();


//    void childCountChanged();
//    void modelDataChanged();
private:
    void onNodeDataChanged(const QModelIndex& index);
    void onNodeChildrenCountChanged(const QModelIndex& index);

private:
//    int m_row = 0;
    QModelIndex m_parentIndex;
    QModelIndex m_currentIndex;
    QmlTreeView* m_view = nullptr;
    int m_childCount = 0;
    QVariant m_modelData;
};

#endif
