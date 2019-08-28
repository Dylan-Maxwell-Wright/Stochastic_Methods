#include "randomwalks.h"
#include "ui_randomwalks.h"
#include "mainwindow.h"
#include "paintingtool.h"
#include "QPainter"
#include "QSlider"
#include "QLineEdit"
#include "QPen"
#include "QRect"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QRandomGenerator"
#include "QtMath"
#include "QAbstractAnimation"
#include "QPropertyAnimation"
#include "lineitem.h"
#include "QSequentialAnimationGroup"
#include "demo.h"


RandomWalks::RandomWalks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomWalks)
{
    ui->setupUi(this);

}

void RandomWalks::buildRandomWalk(QSequentialAnimationGroup* walkingLanes, QGraphicsScene* randomWalk, QPointF startingPoint)
{
    bool outOfArea = false;
    qreal angle;
    QLineF moveVector;
    int testFive = 0;
    while (!outOfArea)
    {
        angle = randomWalkAngle();
        moveVector = createVector(angle, startingPoint);
        walkingLanes->addAnimation(buildRandomWalkHelper(randomWalk, startingPoint, moveVector));
        startingPoint = setCurrentPosition(startingPoint, moveVector);
        outOfArea = outOfBounds(randomWalk->sceneRect(), moveVector.p2());
        testFive++;
    }
}

QPropertyAnimation* RandomWalks::buildRandomWalkHelper(QGraphicsScene *randomWalk,  QPointF startingPoint, QLineF moveVector)
{
    QPropertyAnimation* nextLineAnimation = new QPropertyAnimation();
    QLineF animStartVector;
    LineItem* oneStep = new LineItem;
    qreal durration = (50 * (walkLength * walkLengthMult)) / walkSpeed;

    animStartVector.setLine(startingPoint.x(), startingPoint.y(), startingPoint.x(), startingPoint.y());
    oneStep->setPen(QColor(0, 0, 0, 0));
    connect(nextLineAnimation, SIGNAL(stateChanged(QAbstractAnimation::State, QAbstractAnimation::State)), oneStep, SLOT(makeVisible()));
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

qreal RandomWalks::randomWalkAngle()
{
    qreal angle = 360 * QRandomGenerator::global()->generateDouble();
    return angle;
}

QLineF RandomWalks::createVector(qreal angle, QPointF currentPos)
{

    qreal dX = qCos(angle) * walkLength * walkLengthMult;
    qreal dY = qSin(angle) * walkLength * walkLengthMult;
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
    if(this->isVisible())
    {
        this->hide();
    }
}

void RandomWalks::buildAxis(QGraphicsScene *blankWalkScene)
{
    PaintingTool randomWalkAxisPainter;
    LineItem *xAxis =  new LineItem(randomWalkAxisPainter.xAxis);
    LineItem *yAxis =  new LineItem(randomWalkAxisPainter.yAxis);
    xAxis->setPen(randomWalkAxisPainter.coordinateAxisPen);
    yAxis->setPen(randomWalkAxisPainter.coordinateAxisPen);
    blankWalkScene->addItem(xAxis);
    blankWalkScene->addItem(yAxis);
}

void RandomWalks::on_maxStepLengthSlider_sliderMoved(int position)
{
    ui->maxStepSliderLabel->setNum(position);
    walkLengthMult = position;
}

void RandomWalks::on_walkSpeedSlider_sliderMoved(int position)
{
    ui->walkSpeedSliderLabel->setNum(position);
    walkSpeed = position;
}

void RandomWalks::connectPlays(QSequentialAnimationGroup *animations)
{
    connect(ui->startButton, SIGNAL(pressed()), animations, SLOT(start()));
    connect(ui->startButton, SIGNAL(pressed()), animations, SLOT(resume()));
}

void RandomWalks::connectPauses(QSequentialAnimationGroup *animations)
{
    connect(ui->maxStepLengthSlider, SIGNAL(sliderPressed()), animations, SLOT(pause()));
    connect(ui->walkSpeedSlider, SIGNAL(sliderPressed()), animations, SLOT(pause()));
    connect(ui->pauseButton, SIGNAL(pressed()), animations, SLOT(pause()));
}

void RandomWalks::on_buildButton_clicked()
{
    PaintingTool randomWalkPaintingTool;
    QPainter randomWalkPainter;
    QPen randomWalkPen = randomWalkPaintingTool.randomWalkPen;
    QPointF currentPosition = randomWalkPaintingTool.origin;

    QGraphicsScene* randomWalk = new QGraphicsScene(QRect(100, 50, 600, 550));
    buildAxis(randomWalk);
    QGraphicsView* randomWalkArea = new QGraphicsView(ui->randomWalkArea);

    randomWalkArea->setScene(randomWalk);
    randomWalkArea->render(&randomWalkPainter);
    randomWalkArea->show();

    QSequentialAnimationGroup *randomWalkAnimation = new QSequentialAnimationGroup();
    buildRandomWalk(randomWalkAnimation, randomWalk, currentPosition);

    connectPlays(randomWalkAnimation);
    connectPauses(randomWalkAnimation);
}
