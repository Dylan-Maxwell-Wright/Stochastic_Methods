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
#include "QAbstractAnimation"
#include "QPropertyAnimation"
#include "lineitem.h"
#include "QSequentialAnimationGroup"


RandomWalks::RandomWalks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomWalks)
{
    ui->setupUi(this);

    PaintingTool randomWalkPaintingTool;
    QPainter randomWalkPainter;
    QPen randomWalkPen = randomWalkPaintingTool.randomWalkPen;

    QPointF currentPosition = randomWalkPaintingTool.origin;

    QSequentialAnimationGroup *randomWalkAnimation = new QSequentialAnimationGroup;
    QGraphicsScene* randomWalk = new QGraphicsScene(QRect(100, 50, 600, 550));
    randomWalk->addLine(randomWalkPaintingTool.xAxis, randomWalkPaintingTool.coordinateAxisPen);
    randomWalk->addLine(randomWalkPaintingTool.yAxis, randomWalkPaintingTool.coordinateAxisPen);
    QGraphicsView* randomWalkArea = new QGraphicsView(ui->randomWalkArea);

    randomWalkArea->setScene(randomWalk);
    randomWalkArea->render(&randomWalkPainter);
    randomWalkArea->show();

    buildRandomWalk(randomWalkAnimation, randomWalk, randomWalkPen, currentPosition);

    randomWalkAnimation->start();
}

void RandomWalks::buildRandomWalk(QSequentialAnimationGroup* walkingLanes, QGraphicsScene* randomWalk, QPen walkPen, QPointF startingPoint)
{
    bool outOfArea = false;
    qreal angle;
    QLineF moveVector;
    int testFive = 0;
    while (!outOfArea)
    {
        angle = randomWalkAngle();
        moveVector = createVector(angle, walkLength, startingPoint);
        walkingLanes->addAnimation(buildRandomWalkHelper(randomWalk, walkPen, startingPoint, moveVector));
        startingPoint = setCurrentPosition(startingPoint, moveVector);
        outOfArea = outOfBounds(randomWalk->sceneRect(), moveVector.p2());
        testFive++;
    }
}

QPropertyAnimation* RandomWalks::buildRandomWalkHelper(QGraphicsScene *randomWalk, QPen walkPen, QPointF startingPoint, QLineF moveVector)
{
    QPropertyAnimation* nextLineAnimation = new QPropertyAnimation;
    QLineF animStartVector;
    LineItem* oneStep = new LineItem;

    animStartVector.setLine(startingPoint.x(), startingPoint.y(), startingPoint.x(), startingPoint.y());
    oneStep->setPen(QColor(0, 0, 0, 0));
    QObject::connect(nextLineAnimation, SIGNAL(stateChanged(QAbstractAnimation::State, QAbstractAnimation::State)), oneStep, SLOT(makeVisible()));
    randomWalk->addItem(oneStep);
    oneStep->setLine(animStartVector);
    nextLineAnimation->setTargetObject(oneStep);
    nextLineAnimation->setPropertyName("p2");
    nextLineAnimation->setStartValue(startingPoint);
    nextLineAnimation->setEndValue(moveVector.p2());
    nextLineAnimation->setDuration(1000);

    startingPoint = setCurrentPosition(startingPoint, moveVector);
    return nextLineAnimation;
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

bool RandomWalks::outOfBounds(QRectF sceneArea, QPointF point2)
{
    bool inBounds;
    inBounds = sceneArea.contains(point2);
    return !inBounds;
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
