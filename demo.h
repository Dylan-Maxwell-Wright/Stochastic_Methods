#ifndef DEMO_H
#define DEMO_H

#include <paintingtool.h>
#include <QGraphicsView>
#include <lineitem.h>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QObject>

class Demo
{

public:
    Demo(QGraphicsView*);
    ~Demo();
    void demoRandomWalk(QGraphicsView*);
    void buildDemoRandomWalk(QSequentialAnimationGroup*, QGraphicsScene*, QPointF);


private:
    QPropertyAnimation* buildDemoRandomWalkHelper(QGraphicsScene*, QPointF, QLineF);
    QLineF createVector(qreal, QPointF);
    QPointF setCurrentPosition(QPointF, QLineF);
    bool outOfBounds(QRectF, QPointF);
};

#endif // DEMO_H
