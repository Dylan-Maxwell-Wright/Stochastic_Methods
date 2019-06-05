#ifndef PAINTINGTOOLS_H
#define PAINTINGTOOLS_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

class PaintingTool
{
public:
    PaintingTool();

public:
    void paintRandomWalk(QPainter *painter, QPaintEvent *event, int speedTimer);

private:

};

#endif // PAINTINGTOOLS_H
