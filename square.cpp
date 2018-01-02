#include "square.h"
#include "chessboard.h"
#include <QDebug>

Square::Square(int X, int Y, SquareColor clr, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    setAcceptHoverEvents(true);
    piece = nullptr;
    boardX = X;
    boardY = Y;
    color = clr;
    setRect((X-1)*80, (Y-1)*80, 80, 80);
 //   setPen(QPen(QColor("#78785a")));

}

void Square::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Chessboard *board = (Chessboard*)(scene());
    board->hoveredSquare = this;

}
