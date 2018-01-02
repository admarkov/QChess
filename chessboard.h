#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsScene>
#include "square.h"
#include "piece.h"

class Chessboard : public QGraphicsScene
{

public:

    bool isCheckNow;

    Square* squares[10][10];

    enum PlayerType {blackPlayer, whitePlayer} currentPlayer;

    enum BoardStatus {dragging, plain} status;

    Piece *draggingPiece;
    Square *hoveredSquare;

    Chessboard(QObject *parent);

    void toggleMove();

    QObject *w;

    bool checkMove(QPoint from, QPoint to, bool forCheckCheck = false);
    bool isCheck();

    void restoreSquares();
    void restoreGame();
    void GodsHelp();

    void stopGame(QString message);

};

#endif // CHESSBOARD_H
