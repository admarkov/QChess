#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Piece : public QGraphicsPixmapItem
{
public:

    enum PieceType {king, queen, bishop, knight, rook, pawn} type;
    enum PieceColor {black, white} color;

    Piece(PieceColor Color, PieceType Type, QGraphicsItem *parent = nullptr);

    int fromX, fromY;

//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // PIECE_H
