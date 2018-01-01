#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <QPen>

class Square : public QGraphicsRectItem
{
public:

    enum SquareColor {white, black} color;

    Square(int X, int Y, SquareColor clr, QGraphicsItem *parent = nullptr);

    int boardX, boardY;

};

#endif // SQUARE_H
