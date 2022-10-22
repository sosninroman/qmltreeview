#ifndef QMLTREENODE_H
#define QMLTREENODE_H

#include <QObject>
#include <QQuickItem>
#include <QQmlComponent>
#include <QModelIndex>

class QmlTreeView;
class Selector;

class TreeNodeProperties : public QObject
{
    Q_OBJECT
public:
    explicit TreeNodeProperties(QObject *parent = nullptr);

    Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
    int row() const {return m_row;}
    void setRow(int val);

    Q_PROPERTY(QVariant parentIndex READ parentIndex WRITE setParentIndex NOTIFY parentIndexChanged)
    QVariant parentIndex() const {return m_parentIndex;}
    void setParentIndex(const QVariant& val);

    Q_PROPERTY(QVariant currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    QVariant currentIndex() const {return m_currentIndex;}
    void setCurrentIndex(const QVariant& val);

    Q_PROPERTY(QmlTreeView* view READ view WRITE setView NOTIFY viewChanged)
    QmlTreeView* view() const {return m_view;}
    void setView(QmlTreeView* val);

    Q_PROPERTY(Selector* selector READ selector WRITE setSelector NOTIFY selectorChanged)
    Selector* selector() {return m_selector;}
    void setSelector(Selector* val);

    Q_PROPERTY(int childCount READ childCount WRITE setChildCount NOTIFY childCountChanged)
    int childCount() const {return m_childCount;}
    void setChildCount(int val);

    Q_PROPERTY(QVariant modelData READ modelData WRITE setModelData NOTIFY modelDataChanged)
    QVariant modelData() const {return m_modelData;}
    void setModelData(const QVariant& val);

    Q_PROPERTY(int contentWidth READ contentWidth WRITE setContentWidth NOTIFY contentWidthChanged)
    int contentWidth() const {return m_contentWidth;}
    void setContentWidth(int val);

signals:
    void rowChanged();
    void parentIndexChanged();
    void currentIndexChanged();
    void viewChanged();
    void selectorChanged();
    void childCountChanged();
    void modelDataChanged();
    void contentWidthChanged();

private:
    int m_row = 0;
    QModelIndex m_parentIndex;
    QModelIndex m_currentIndex;
    QmlTreeView* m_view = nullptr;
    Selector* m_selector = nullptr;
    int m_childCount = 0;
    QVariant m_modelData;
    int m_contentWidth = 0;
};

#endif
