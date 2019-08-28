#ifndef DEMO_H
#define DEMO_H

#include <paintingtool.h>
#include <QGraphicsView>
#include <lineitem.h>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QObject>

class demo: public QObject
{
    Q_OBJECT

public:
    demo(QGraphicsView*);
    ~demo();
    void demoRandomWalk(QGraphicsView*);
    void buildDemoRandomWalk(QSequentialAnimationGroup*, QGraphicsScene*, QPointF);


private:
    QPropertyAnimation* buildDemoRandomWalkHelper(QGraphicsScene*, QPointF, QLineF);
    QLineF createVector(qreal, QPointF);
    QPointF setCurrentPosition(QPointF, QLineF);
    bool outOfBounds(QRectF, QPointF);
};

#endif // DEMO_H
