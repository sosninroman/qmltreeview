#ifndef QMLTREEVIEW_H
#define QMLTREEVIEW_H

#include <QObject>
#include <QQuickItem>
#include "selector.h"

class QmlTreeView : public QQuickItem
{
    Q_OBJECT
public:
    explicit QmlTreeView(QQuickItem *parent = nullptr);

    Q_PROPERTY(Selector* selector READ selector CONSTANT)
    Selector* selector() {return &m_selector;}

//    Q_INVOKABLE void listenTo(QObject *object)
//    {
//        if (!object)
//            return;

//        object->installEventFilter(this);
//    }

//    bool eventFilter(QObject *object, QEvent *event) override
//    {
//        qCritical() << "v";
//        if (event->type() == QEvent::MouseButtonRelease) {
//            //QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
//            //qDebug() << "key" << keyEvent->key() << "pressed on" << object;
//            qCritical() << "mouse clicked";
//            return true;
//        }
//        return false;
//    }

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

private:
//    bool event(QEvent* event) override
//    {
//        qCritical() << "mouse event" << event->type() << "\n";
//        return true;
//    }
private:
    Selector m_selector;
};

#endif
