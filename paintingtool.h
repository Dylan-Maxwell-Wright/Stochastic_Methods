#ifndef PAINTINGTOOLS_H
#define PAINTINGTOOLS_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QLineF>

class PaintingTool
{
public:
    PaintingTool();

public:
    void paintRandomWalk(QPainter *painter, QPaintEvent *event, int speedTimer);
    void setMaxStep(float m);

private:
    QLineF randomInterval;
    float maxStep;
    float walkSpeed;
    float angle;

};

#endif // PAINTINGTOOLS_H
