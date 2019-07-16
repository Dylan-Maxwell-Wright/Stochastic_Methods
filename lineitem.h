#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsLineItem>
#include <QObject>

class LineItem: public QObject, public QGraphicsLineItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF p1 READ p1 WRITE setP1)
    Q_PROPERTY(QPointF p2 READ p2 WRITE setP2)

public:
    using QGraphicsLineItem::QGraphicsLineItem;

    QPointF p1() const {
        return  line().p1();
    }

    void setP1(const QPointF & p){
        QLineF l = line();
        l.setP1(p);
        setLine(l);
    }

    QPointF p2() const {
        return  line().p2();
    }

    void setP2(const QPointF & p){
        QLineF l = line();
        l.setP2(p);
        setLine(l);
    }
};

#endif // LINEITEM_H
