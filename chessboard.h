#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsScene>
#include "square.h"
#include "piece.h"

class Chessboard : public QGraphicsScene
{

public:

    Square* squares[10][10];

    enum PlayerType {blackPlayer, whitePlayer} currentPlayer;

    enum BoardStatus {dragging, plain} status;

    Piece *draggingPiece;
    Square *hoveredSquare;

    Chessboard(QObject *parent);

    void toggleMove();

    QObject *w;

};

#endif // CHESSBOARD_H
