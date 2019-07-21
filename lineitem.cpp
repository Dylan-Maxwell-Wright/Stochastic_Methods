#include "lineitem.h"
#include "paintingtool.h"

void LineItem::makeVisible()
{
    PaintingTool randomWalkPaintingTool;
    setPen(randomWalkPaintingTool.randomWalkPen);
}

