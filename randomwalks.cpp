#include "randomwalks.h"
#include "ui_randomwalks.h"
#include "mainwindow.h"
#include "paintingtool.h"
#include "QPainter"
#include "QSlider"
#include "QLineEdit"
#include "QPen"
#include "QRect"
#include "QPicture"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QRandomGenerator"
#include "QtMath"
#include "QPropertyAnimation"
#include "lineitem.h"
#include "QSequentialAnimationGroup"


RandomWalks::RandomWalks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomWalks)
{
    ui->setupUi(this);
    timer = new QTimer();

    PaintingTool randomWalkPaintingTool;
    QPicture randomWalkPicture;
    QPainter randomWalkPainter;
    QLineF testLine(100, 50, 600, 550);
    QPen randomWalkPen = randomWalkPaintingTool.randomWalkPen;

    QPointF currentPosition = randomWalkPaintingTool.origin;

    QSequentialAnimationGroup *randomWalkAnimation = new QSequentialAnimationGroup;
    QGraphicsScene* randomWalk = new QGraphicsScene(QRect(100, 50, 600, 550));
    randomWalk->addLine(randomWalkPaintingTool.xAxis, randomWalkPaintingTool.coordinateAxisPen);
    randomWalk->addLine(randomWalkPaintingTool.yAxis, randomWalkPaintingTool.coordinateAxisPen);
    QGraphicsView* randomWalkArea = new QGraphicsView(ui->randomWalkArea);

    QPropertyAnimation* animatedWalk = new QPropertyAnimation();
    //bool stepTaken = paintRandomWalk(randomWalk, randomWalkPaintingTool.randomWalkPen, &currentPosition);
    randomWalkArea->setScene(randomWalk);
    randomWalkArea->render(&randomWalkPainter);
    randomWalkArea->show();

    buildRandomWalk(randomWalkAnimation, randomWalk, randomWalkPen, currentPosition);

    randomWalkAnimation->start();
}

void RandomWalks::buildRandomWalk(QSequentialAnimationGroup* walkingLanes, QGraphicsScene* randomWalk, QPen walkPen, QPointF startingPoint)
{
    /*
    QPropertyAnimation* nextLineAnimation = new QPropertyAnimation;
    QLineF animStartVector, moveVector;
    LineItem* oneStep = new LineItem;
    qreal angle;
    qreal tempLength = 100;
    bool hitEdge = false;
    int testFive = 0;
    while (testFive < 5)
    {
        angle = randomWalkAngle();
        animStartVector.setLine(startingPoint.x(), startingPoint.y(), startingPoint.x(), startingPoint.y());
        moveVector = createVector(angle, tempLength, startingPoint);
        oneStep->setPen(walkPen);
        randomWalk->addItem(oneStep);
        oneStep->setLine(animStartVector);
        nextLineAnimation->setTargetObject(oneStep);
        nextLineAnimation->setPropertyName("p2");
        nextLineAnimation->setStartValue(startingPoint);
        nextLineAnimation->setEndValue(moveVector.p2());
        nextLineAnimation->setDuration(1000);
        walkingLanes->addAnimation(nextLineAnimation);
        nextLineAnimation->start();
        startingPoint = setCurrentPosition(startingPoint, moveVector);
        testFive++;
    }*/
    qreal angle;
    QLineF moveVector;
    int testFive = 0;
    while (testFive < 5)
    {
        angle = randomWalkAngle();
        moveVector = createVector(angle, walkLength, startingPoint);
        walkingLanes->addAnimation(buildRandomWalkHelper(randomWalk, walkPen, startingPoint, moveVector));
        startingPoint = setCurrentPosition(startingPoint, moveVector);
        testFive++;
    }
}

QPropertyAnimation* RandomWalks::buildRandomWalkHelper(QGraphicsScene *randomWalk, QPen walkPen, QPointF startingPoint, QLineF moveVector)
{
    QPropertyAnimation* nextLineAnimation = new QPropertyAnimation;
    QLineF animStartVector;
    LineItem* oneStep = new LineItem;
    qreal angle;
    qreal tempLength = 1000;

    animStartVector.setLine(startingPoint.x(), startingPoint.y(), startingPoint.x(), startingPoint.y());
    oneStep->setPen(walkPen);
    randomWalk->addItem(oneStep);
    oneStep->setLine(animStartVector);
    nextLineAnimation->setTargetObject(oneStep);
    nextLineAnimation->setPropertyName("p2");
    nextLineAnimation->setStartValue(startingPoint);
    nextLineAnimation->setEndValue(moveVector.p2());
    nextLineAnimation->setDuration(1000);

    //nextLineAnimation->start();
    startingPoint = setCurrentPosition(startingPoint, moveVector);
    return nextLineAnimation;
}

bool RandomWalks::paintRandomWalk(QGraphicsScene* randomWalk, QPen walkPen, QPointF *currentPosition)
{

    QTimer* stopwatch = new QTimer(randomWalk);
    qreal fixedLength = 100;
    qreal fixedSpeed = 1;
    qreal angle = randomWalkAngle();
    QLineF moveVector, startVector;

    moveVector = createVector(angle, fixedLength, *currentPosition);
    startVector.setLine(currentPosition->x(), currentPosition->y(), currentPosition->x(), currentPosition->y());

    //QGraphicsLineItem *item = randomWalk->addLine(startVector, walkPen);

    LineItem *lineItem = new LineItem(QLineF(QPointF(currentPosition->x(), currentPosition->y()), QPointF(currentPosition->x(), currentPosition->y())));
    randomWalk->addItem(lineItem);
    lineItem->setPen(walkPen);

    //QPropertyAnimation* animatedWalk = this->animatedWalk;
    QPropertyAnimation* animatedWalk = new QPropertyAnimation(lineItem, "p2");
    animatedWalk->setTargetObject(lineItem);
    animatedWalk->setPropertyName("p2");
    animatedWalk->setStartValue(*currentPosition);
    animatedWalk->setEndValue(moveVector.p2());
    animatedWalk->setDuration(1000);

    *currentPosition = setCurrentPosition(*currentPosition, moveVector);
    //connect(animatedWalk, SIGNAL(finished()), this, SLOT(walkSlow()));
    animatedWalk->start();



    /*animatedWalk->setDuration(1000/fixedSpeed);
    animatedWalk->setStartValue(startVector);
    animatedWalk->setEndValue(moveVector);
    //randomWalk->addLine(moveVector, walkPen);
    animatedWalk->start();

    */
    //findCurrentPositon Test ---- pass

    /*
    angle = randomWalkAngle();
    moveVector = createVector(angle, fixedLength, *currentPosition);
    randomWalk->addLine(moveVector, walkPen);
    *currentPosition = findCurrentPosition(*currentPosition, moveVector);
    */


    return true;
}


void RandomWalks::walkSlow ()
{
    qreal angle = randomWalkAngle();
    QPointF startingPoint = currentPosition;
    QLineF moveVector = createVector(angle, walkLength, startingPoint);
    QLineF startVector;
    startVector.setLine(startingPoint.x(), startingPoint.y(), startingPoint.x(), startingPoint.y());

    //QGraphicsLineItem *item = randomWalk->addLine(startVector, walkPen);

    LineItem *lineItem = new LineItem(startVector);
    //QGraphicsScene* randomWalkTemp = randomWalk;
    //randomWalk->addItem(lineItem);
    //lineItem->setPen(randomWalkPen);


    QPropertyAnimation* animatedWalk = new QPropertyAnimation(lineItem, "p2");
    animatedWalk->setStartValue(startingPoint);
    animatedWalk->setEndValue(moveVector.p2());


    animatedWalk->setDuration(10000);
    animatedWalk->start();
}

qreal RandomWalks::randomWalkAngle()
{
    qreal angle = 360 * QRandomGenerator::global()->generateDouble();
    return angle;
}

QLineF RandomWalks::createVector(qreal angle, qreal length, QPointF currentPos)
{

    qreal dX = qCos(angle) * length;
    qreal dY = qSin(angle) * length;
    QPointF finalPos(currentPos.x() + dX, currentPos.y() + dY);
    QLineF mathVector(currentPos, finalPos);

    /*
    currentPos->setX(finalPos.x());
    currentPos->setY(finalPos.x());
     //set this only after successful walk
    */
    return mathVector;

}

QPointF RandomWalks::setCurrentPosition(QPointF lastPos, QLineF moveVec)
{
    QPointF finalPos;
    qreal finalX = lastPos.x() + moveVec.dx();
    qreal finalY = lastPos.y() + moveVec.dy();
    finalPos.setX(finalX);
    finalPos.setY(finalY);

    return finalPos;
}



RandomWalks::~RandomWalks()
{
    delete ui;
}


void RandomWalks::on_backMain_clicked()
{
    close();
}

void RandomWalks::close()
{
    if(this->isVisible())
    {
        this->hide();
    }
}


void RandomWalks::on_maxStepLengthSlider_sliderMoved(int position)
{
    ui->maxStepSliderLabel->setNum(position);
}
