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

    void on_walkSpeedSlider_sliderMoved(int position);

    void on_buildButton_clicked();

private:
    QGraphicsView *randomWalkArea;
    QGraphicsScene *randomWalk;
    Ui::RandomWalks *ui;
    QLabel *maxStepSliderLabel, *walkSpeedSliderLabel;
    QSlider *maxStepSlider, *walkSpeedSlider;
    QPropertyAnimation *animatedWalk;
    QSequentialAnimationGroup *randomWalkAnimation;
    QPen randomWalkPen;



    //random walk methods
    void buildAxis(QGraphicsScene*);
    qreal randomWalkAngle();
    QLineF createVector(qreal, QPointF);
    QPointF setCurrentPosition(QPointF, QLineF);
    void buildRandomWalk(QSequentialAnimationGroup*, QGraphicsScene*, QPointF);
    QPropertyAnimation* buildRandomWalkHelper(QGraphicsScene*, QPointF, QLineF);
    bool outOfBounds(QRectF, QPointF);
    void connectPlays(QSequentialAnimationGroup*);
    void connectPauses(QSequentialAnimationGroup*);

    //random walk variables
    qreal walkLength = 20;
    qreal walkLengthMult = 1;
    qreal walkSpeed = 1;
    QPointF currentPosition;

};




#endif // RANDOMWALKS_H
