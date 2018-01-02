#include "piece.h"
#include "chessboard.h"
#include "mainwindow.h"

#include <QPixmap>
#include <QDebug>

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

/*void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Chessboard *board = (Chessboard*)(scene());
    MainWindow *W = (MainWindow*)(board->w);
    board->status = Chessboard::dragging;
    event->accept();
}*/

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Chessboard *board = (Chessboard*)(scene());
    board->restoreSquares();
    board->draggingPiece = nullptr;
    int boardX = (pos().x() + 40)/80+1,
        boardY = (pos().y() +40)/80+1;
    if (boardX < 1) boardX = 1;
    if (boardY < 1) boardY = 1;
    if (boardX > 8) boardX = 8;
    if (boardY > 8) boardY = 8;
    if (board->checkMove(QPoint(fromX, fromY), QPoint(boardX, boardY))) {
        setPos(boardX*80 - 80, boardY*80 - 80);
        if (board->squares[boardY][boardX]->piece!=nullptr) {
            board->removeItem(board->squares[boardY][boardX]->piece);
            delete board->squares[boardY][boardX]->piece;
        }
        board->squares[fromY][fromX]->piece = nullptr;
        board->squares[boardY][boardX]->piece = this;
        board->toggleMove();
    }
    else {
        setPos(fromX*80 - 80, fromY*80 - 80);
    }
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}
void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    Chessboard *board = (Chessboard*)(scene());
    int boardX = (pos().x() + 40)/80+1,
        boardY = (pos().y() +40)/80+1;
    if (boardX < 1) boardX = 1;
    if (boardY < 1) boardY = 1;
    if (boardX > 8) boardX = 8;
    if (boardY > 8) boardY = 8;
    if (board->draggingPiece != this) {
        fromX = boardX;
        fromY = boardY;
        board->draggingPiece = this;
    }
    board->restoreSquares();
    Square *hoveredSquare = board->squares[boardY][boardX];
    if (board->checkMove(QPoint(fromX, fromY), QPoint(boardX, boardY))) {
        if (board->squares[boardY][boardX]->piece!=nullptr)
            hoveredSquare->setBrush(QBrush(Qt::yellow));
        else
            hoveredSquare->setBrush(QBrush(Qt::green));
    }
    else
        hoveredSquare->setBrush(QBrush(Qt::red));
    QGraphicsPixmapItem::mouseMoveEvent(event);
}
