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

    QPointF currentPosition = randomWalkPaintingTool.origin;

    QGraphicsScene* randomWalk = new QGraphicsScene(QRect(100, 50, 600, 550));
    randomWalk->addLine(randomWalkPaintingTool.xAxis, randomWalkPaintingTool.coordinateAxisPen);
    randomWalk->addLine(randomWalkPaintingTool.yAxis, randomWalkPaintingTool.coordinateAxisPen);

    bool stepTaken = paintRandomWalk(randomWalk, randomWalkPaintingTool.randomWalkPen, &currentPosition);

    QGraphicsView* randomWalkArea = new QGraphicsView(ui->randomWalkArea);
    randomWalkArea->setScene(randomWalk);
    randomWalkArea->render(&randomWalkPainter);


}

bool RandomWalks::paintRandomWalk(QGraphicsScene* randomWalk, QPen walkPen, QPointF *currentPosition)
{
    QPropertyAnimation* animatedWalk = new QPropertyAnimation(randomWalk, "lines");
    QTimer* stopwatch = new QTimer(randomWalk);
    qreal fixedLength = 100;
    qreal fixedSpeed = 1;
    qreal angle = randomWalkAngle();
    QLineF moveVector, startVector;
    moveVector = createVector(angle, fixedLength, *currentPosition);
    startVector.setLine(currentPosition->x(), currentPosition->y(), currentPosition->x(), currentPosition->y());

    animatedWalk->setDuration(1000/fixedSpeed);
    animatedWalk->setStartValue(startVector);
    animatedWalk->setEndValue(moveVector);
    //randomWalk->addLine(moveVector, walkPen);
    animatedWalk->start();
    *currentPosition = findCurrentPosition(*currentPosition, moveVector);

    //findCurrentPositon Test ---- pass

    /*
    angle = randomWalkAngle();
    moveVector = createVector(angle, fixedLength, *currentPosition);
    randomWalk->addLine(moveVector, walkPen);
    *currentPosition = findCurrentPosition(*currentPosition, moveVector);
    */


    return true;
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

QPointF RandomWalks::findCurrentPosition(QPointF lastPos, QLineF moveVec)
{
    QPointF finalPos;
    qreal finalX = lastPos.x() + moveVec.dx();
    qreal finalY = lastPos.y() + moveVec.dy();
    finalPos.setX(finalX);
    finalPos.setY(finalY);

    return finalPos;
}

void RandomWalks::walkSlow (QLineF moveVector, QPen walkPen, qreal Length, qreal Speed, QTimer* stopwatch)
{

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
