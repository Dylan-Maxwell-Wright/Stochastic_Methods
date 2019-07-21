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
    QPen randomWalkPen;

    QPen coordinateAxisPen;
    QLineF yAxis;
    QLineF xAxis;
    QPointF origin;


public:

private:

};

#endif // PAINTINGTOOLS_H
