#ifndef RANDOMWALKS_H
#define RANDOMWALKS_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "paintingtool.h"
#include "QPicture"
#include <QRandomGenerator>
#include <QtMath>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>


namespace Ui {
class RandomWalks;
}

class RandomWalks : public QDialog
{
    Q_OBJECT

public:
    explicit RandomWalks(QWidget *parent = nullptr);
    ~RandomWalks();

signals:
    void sliderPressed();

private slots:
    void on_maxStepLengthSlider_sliderMoved(int position);

    void on_backMain_clicked();

    void close();

    void walkSlow();

private:
    QGraphicsView *randomWalkArea;
    QGraphicsScene *randomWalk;
    Ui::RandomWalks *ui;
    QTimer * timer;
    PaintingTool *randomWalkPainter;
    QLabel *maxStepSliderLabel;
    QSlider *maxStepSlider;
    QPropertyAnimation *animatedWalk;
    QSequentialAnimationGroup *walkingGroup;



    qreal randomWalkAngle();
    QLineF createVector(qreal, qreal, QPointF);
    QPointF setCurrentPosition(QPointF, QLineF);
    bool paintRandomWalk(QGraphicsScene*, QPen, QPointF*);
    void buildRandomWalk(QSequentialAnimationGroup*, QGraphicsScene*, QPen, QPointF);
    QPropertyAnimation* buildRandomWalkHelper(QGraphicsScene*, QPen, QPointF, QLineF);
    QPen randomWalkPen;


    //random walk variables
    qreal walkLength = 20;
    qreal walkLengthMult = 5;
    qreal walkSpeed = 1;
    qreal walkSpeedMult = 1;
    QPointF currentPosition;



};




#endif // RANDOMWALKS_H
