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

    bool stepTaken = paintRandomWalk(randomWalk, randomWalkPaintingTool.randomWalkPen, currentPosition);

    QGraphicsView* randomWalkArea = new QGraphicsView(ui->randomWalkArea);
    randomWalkArea->setScene(randomWalk);
    randomWalkArea->render(&randomWalkPainter);


}

bool RandomWalks::paintRandomWalk(QGraphicsScene* randomWalk, QPen walkPen, QPointF currentPosition)
{

    qreal fixedLength = 100;
    qreal fixedSpeed = 1;
    qreal angle = randomWalkAngle();
    QLineF moveVector;
    QPointF testPoint1(350, 300);
    moveVector.setP1(testPoint1);
    QPointF testPoint2(400, 450);
    moveVector = createVector(angle, fixedLength, currentPosition);
    //moveVector.setP2(testPoint2);//createVector(angle, fixedLength, currentPosition);
    randomWalk->addLine(moveVector, walkPen);


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
