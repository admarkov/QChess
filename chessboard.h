#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsScene>
#include "square.h"
#include "piece.h"
#include "pawnpromotiondialog.h"

class Chessboard : public QGraphicsScene
{

public:

    PawnPromotionDialog *ppd;

    bool isCheckNow;
    bool noBlackLeftCastling, noBlackRightCastling;
    bool noWhiteLeftCastling, noWhiteRightCastling;

    int pawnX, pawnY;

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
    bool isCheckmate();

    void restoreSquares();
    void restoreGame();
    void GodsHelp();

    void stopGame(QString message);

    bool isLeftCastlingAble();
    bool isRightCastlingAble();
    bool checkCastlingPosition(int x, int y);
    void leftCastling();
    void rightCastling();

    void pawnToRook();
    void pawnToKnight();
    void pawnToBishop();
    void pawnToQueen();

};

#endif // CHESSBOARD_H
