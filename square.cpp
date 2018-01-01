#include "square.h"

Square::Square(int X, int Y, SquareColor clr, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{

    boardX = X;
    boardY = Y;
    color = clr;
    if (clr == black)
        setBrush(QBrush(QColor("#78785a")));
    else
        setBrush(QBrush(QColor("#d3d39e")));
    setRect((X-1)*80, (Y-1)*80, 80, 80);
 //   setPen(QPen(QColor("#78785a")));

}
