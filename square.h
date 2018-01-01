#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QPen>
#include "piece.h"
#include <QHoverEvent>
#include <QGraphicsSceneHoverEvent>

class Square : public QGraphicsRectItem
{
public:

    enum SquareColor {white, black} color;

    Square(int X, int Y, SquareColor clr, QGraphicsItem *parent = nullptr);

    int boardX, boardY;

    Piece *piece;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

};

#endif // SQUARE_H
