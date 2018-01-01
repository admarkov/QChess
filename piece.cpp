#include "piece.h"

#include <QPixmap>

Piece::Piece(PieceColor Color, PieceType Type, QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent)
{
    type = Type;
    color = Color;
    setOffset(9,10);
    if (color == white) {
        if (type==king)
            setPixmap(QPixmap(":/Images/king_white.svg"));
        if (type==queen)
            setPixmap(QPixmap(":/Images/queen_white.svg"));
        if (type==bishop)
            setPixmap(QPixmap(":/Images/bishop_white.svg"));
        if (type==knight)
            setPixmap(QPixmap(":/Images/knight_white.svg"));
        if (type==rook)
            setPixmap(QPixmap(":/Images/rook_white.svg"));
        if (type==pawn)
            setPixmap(QPixmap(":/Images/pawn_white.svg"));
    }
    else {
        if (type==king)
            setPixmap(QPixmap(":/Images/king_black.svg"));
        if (type==queen)
            setPixmap(QPixmap(":/Images/queen_black.svg"));
        if (type==bishop)
            setPixmap(QPixmap(":/Images/bishop_black.svg"));
        if (type==knight)
            setPixmap(QPixmap(":/Images/knight_black.svg"));
        if (type==rook)
            setPixmap(QPixmap(":/Images/rook_black.svg"));
        if (type==pawn)
            setPixmap(QPixmap(":/Images/pawn_black.svg"));
    }
}
