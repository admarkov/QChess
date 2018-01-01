#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>

class Piece : public QGraphicsPixmapItem
{
public:

    enum PieceType {king, queen, bishop, knight, rook, pawn} type;
    enum PieceColor {black, white} color;

    Piece(PieceColor Color, PieceType Type, QGraphicsItem *parent = nullptr);
};

#endif // PIECE_H
