#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QPen>
#include "piece.h"

class Square : public QGraphicsRectItem
{
public:

    enum SquareColor {white, black} color;

    Square(int X, int Y, SquareColor clr, QGraphicsItem *parent = nullptr);

    int boardX, boardY;

    Piece *piece;

};

#endif // SQUARE_H
