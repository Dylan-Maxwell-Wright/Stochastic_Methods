#include "demo.h"
#include "QSequentialAnimationGroup"
#include "QtMath"
#include "lineitem.h"
#include "QObject"

demo::demo(QGraphicsView *target)
{
    demoRandomWalk(target);
}

void demo::demoRandomWalk(QGraphicsView *targetView)
{
    QGraphicsScene* randomWalkDemo = new QGraphicsScene(targetView->rect());
    QGraphicsView* randomWalkDemoArea = new QGraphicsView(targetView);
    PaintingTool randomWalkPaintingTool;
    QPainter randomWalkPainter;
    QPen randomWalkPen = randomWalkPaintingTool.randomWalkPen;
    QPointF currentPosition = targetView->rect().center();

    randomWalkDemoArea->setScene(randomWalkDemo);
    randomWalkDemoArea->render(&randomWalkPainter);
    randomWalkDemoArea->show();

    QSequentialAnimationGroup *randomWalkAnimation = new QSequentialAnimationGroup();
    buildDemoRandomWalk(randomWalkAnimation, randomWalkDemo, currentPosition);
    randomWalkAnimation->setLoopCount(-1);
    randomWalkAnimation->start();

}

void demo::buildDemoRandomWalk(QSequentialAnimationGroup* walkingLanes, QGraphicsScene* randomWalk, QPointF startingPoint)
{
    bool outOfArea = false;
    qreal angle;
    QLineF moveVector;
    while (!outOfArea)
    {
        angle = 360 * QRandomGenerator::global()->generateDouble();
        moveVector = createVector(angle, startingPoint);
        walkingLanes->addAnimation(buildDemoRandomWalkHelper(randomWalk, startingPoint, moveVector));
        startingPoint = setCurrentPosition(startingPoint, moveVector);
        outOfArea = outOfBounds(randomWalk->sceneRect(), moveVector.p2());
    }
}

QLineF demo::createVector(qreal angle, QPointF currentPos)
{

    qreal dX = qCos(angle) * 20;
    qreal dY = qSin(angle) * 20;
    QPointF finalPos(currentPos.x() + dX, currentPos.y() + dY);
    QLineF mathVector(currentPos, finalPos);

    return mathVector;
}

QPropertyAnimation* demo::buildDemoRandomWalkHelper(QGraphicsScene *randomWalk,  QPointF startingPoint, QLineF moveVector)
{
    QPropertyAnimation* nextLineAnimation = new QPropertyAnimation();
    QLineF animStartVector;
    LineItem* oneStep = new LineItem;
    qreal durration = (50 * 10) / 1.5;

    animStartVector.setLine(startingPoint.x(), startingPoint.y(), startingPoint.x(), startingPoint.y());
    oneStep->setPen(QColor(0, 0, 0, 0));
    QObject::connect(nextLineAnimation, SIGNAL(stateChanged(QAbstractAnimation::State, QAbstractAnimation::State)), oneStep, SLOT(makeVisible()));
    randomWalk->addItem(oneStep);
    randomWalk->selectedItems().push_back(oneStep);
    oneStep->setLine(animStartVector);
    nextLineAnimation->setTargetObject(oneStep);
    nextLineAnimation->setPropertyName("p2");
    nextLineAnimation->setStartValue(startingPoint);
    nextLineAnimation->setEndValue(moveVector.p2());
    nextLineAnimation->setDuration(int(durration));

    startingPoint = setCurrentPosition(startingPoint, moveVector);
    return nextLineAnimation;
}

QPointF demo::setCurrentPosition(QPointF lastPos, QLineF moveVec)
{
    QPointF finalPos;
    qreal finalX = lastPos.x() + moveVec.dx();
    qreal finalY = lastPos.y() + moveVec.dy();
    finalPos.setX(finalX);
    finalPos.setY(finalY);

    return finalPos;
}

bool demo::outOfBounds(QRectF sceneArea, QPointF point2)
{
    bool inBounds;
    inBounds = sceneArea.contains(point2);
    return !inBounds;
}
