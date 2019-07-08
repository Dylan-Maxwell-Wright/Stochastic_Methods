#include "paintingtool.h"
#include "QPainter"
#include "QLineF"
#include "QPen"

PaintingTool::PaintingTool()
{
    PaintingTool::randomWalkPen.setStyle(Qt::SolidLine);
    PaintingTool::randomWalkPen.setColor(Qt::darkBlue);
    PaintingTool::randomWalkPen.setWidth(2);

    PaintingTool::coordinateAxisPen.setStyle(Qt::SolidLine);
    PaintingTool::coordinateAxisPen.setColor(Qt::black);
    PaintingTool::coordinateAxisPen.setWidth(2);

    PaintingTool::xAxis.setLine(100, 300, 600, 300);
    PaintingTool::yAxis.setLine(350, 50, 350, 550);

    PaintingTool::origin.setX(350);
    PaintingTool::origin.setY(300);
}

void PaintingTool::paintRandomWalk(QPainter *painter, QPaintEvent *event, int speedTimer)
{

}



