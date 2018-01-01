#include "chessboard.h"

Chessboard::Chessboard(QObject *parent)
    : QGraphicsScene(parent)
{
    currentPlayer = blackPlayer;

    for (int i=0 ;i<10; i++)
        for (int j=0; j<10; j++)
            squares[i][j] = nullptr;

    for (int y=1; y<=8; y++)
        for (int x=1; x<=8; x++) {
            squares[y][x] = new Square(x, y, (x+y)%2?Square::black:Square::white);
            addItem(squares[y][x]);
        }

    toggleMove();

}

void Chessboard::toggleMove() {
    if (currentPlayer == blackPlayer)
        currentPlayer = whitePlayer;
    else
        currentPlayer = blackPlayer;
    for (int i=1; i<=8; i++)
        for (int j=1; j<=8; j++) {
            if (squares[i][j]->piece!=nullptr) {
                Piece *piece = squares[i][j]->piece;
                if (currentPlayer == blackPlayer) {
                    if (piece->color == Piece::white)
                        piece->setFlag(QGraphicsItem::ItemIsMovable, false);
                    else
                        piece->setFlag(QGraphicsItem::ItemIsMovable, true);
                }
                else {
                    if (piece->color == Piece::white)
                        piece->setFlag(QGraphicsItem::ItemIsMovable, true);
                    else
                        piece->setFlag(QGraphicsItem::ItemIsMovable, false);
                }
            }
        }
}
