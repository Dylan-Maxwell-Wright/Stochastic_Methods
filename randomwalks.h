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

private:
    QGraphicsView *randomWalkArea;
    QGraphicsScene *randomWalk;
    Ui::RandomWalks *ui;
    QTimer * timer;
    PaintingTool *randomWalkPainter;
    QLabel *maxStepSliderLabel;
    QSlider *maxStepSlider;
    QPicture randomWalkPicture;

    bool paintRandomWalk(QGraphicsScene*, QPen, QPointF);

    qreal randomWalkAngle();
    QLineF createVector(double, double, QPointF);

    //random walk variables
    qreal walkLength = 1;
    qreal walkLengthMult = 5;
    qreal walkSpeed = 1;
    qreal walkSpeedMult = 1;
    QPointF currentPosition;


};




#endif // RANDOMWALKS_H
