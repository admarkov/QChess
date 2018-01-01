#include "chessboard.h"
#include "mainwindow.h"
#include <algorithm>

using namespace std;

Chessboard::Chessboard(QObject *parent)
    : QGraphicsScene(parent)
{

    w = parent;
    draggingPiece = nullptr;

    currentPlayer = blackPlayer;

    for (int i=0 ;i<10; i++)
        for (int j=0; j<10; j++)
            squares[i][j] = nullptr;

    for (int y=1; y<=8; y++)
        for (int x=1; x<=8; x++) {
            squares[y][x] = new Square(x, y, (x+y)%2?Square::black:Square::white);
            addItem(squares[y][x]);
        }

    squares[1][1]->piece = new Piece(Piece::black, Piece::rook);
    addItem(squares[1][1]->piece);
    squares[1][1]->piece->setPos(0, 0);

    squares[1][2]->piece = new Piece(Piece::black, Piece::knight);
    addItem(squares[1][2]->piece);
    squares[1][2]->piece->setPos(80, 0);

    squares[1][3]->piece = new Piece(Piece::black, Piece::bishop);
    addItem(squares[1][3]->piece);
    squares[1][3]->piece->setPos(80*2, 0);

    squares[1][4]->piece = new Piece(Piece::black, Piece::queen);
    addItem(squares[1][4]->piece);
    squares[1][4]->piece->setPos(80*3, 0);

    squares[1][5]->piece = new Piece(Piece::black, Piece::king);
    addItem(squares[1][5]->piece);
    squares[1][5]->piece->setPos(80*4, 0);

    squares[1][6]->piece = new Piece(Piece::black, Piece::bishop);
    addItem(squares[1][6]->piece);
    squares[1][6]->piece->setPos(80*5, 0);

    squares[1][7]->piece = new Piece(Piece::black, Piece::knight);
    addItem(squares[1][7]->piece);
    squares[1][7]->piece->setPos(80*6, 0);

    squares[1][8]->piece = new Piece(Piece::black, Piece::rook);
    addItem(squares[1][8]->piece);
    squares[1][8]->piece->setPos(80*7, 0);


    squares[8][1]->piece = new Piece(Piece::white, Piece::rook);
    addItem(squares[8][1]->piece);
    squares[8][1]->piece->setPos(0, 80*7);

    squares[8][2]->piece = new Piece(Piece::white, Piece::knight);
    addItem(squares[8][2]->piece);
    squares[8][2]->piece->setPos(80, 80*7);

    squares[8][3]->piece = new Piece(Piece::white, Piece::bishop);
    addItem(squares[8][3]->piece);
    squares[8][3]->piece->setPos(80*2, 80*7);

    squares[8][4]->piece = new Piece(Piece::white, Piece::queen);
    addItem(squares[8][4]->piece);
    squares[8][4]->piece->setPos(80*3, 80*7);

    squares[8][5]->piece = new Piece(Piece::white, Piece::king);
    addItem(squares[8][5]->piece);
    squares[8][5]->piece->setPos(80*4, 80*7);

    squares[8][6]->piece = new Piece(Piece::white, Piece::bishop);
    addItem(squares[8][6]->piece);
    squares[8][6]->piece->setPos(80*5, 80*7);

    squares[8][7]->piece = new Piece(Piece::white, Piece::knight);
    addItem(squares[8][7]->piece);
    squares[8][7]->piece->setPos(80*6, 80*7);

    squares[8][8]->piece = new Piece(Piece::white, Piece::rook);
    addItem(squares[8][8]->piece);
    squares[8][8]->piece->setPos(80*7, 80*7);

    for (int i=1; i<=8; i++) {
        squares[2][i]->piece = new Piece(Piece::black, Piece::pawn);
        addItem(squares[2][i]->piece);
        squares[2][i]->piece->setPos(80*i-80, 80);

        squares[7][i]->piece = new Piece(Piece::white, Piece::pawn);
        addItem(squares[7][i]->piece);
        squares[7][i]->piece->setPos(80*i-80, 80*6);
    }

    toggleMove();

}

void Chessboard::toggleMove() {
    MainWindow *W = (MainWindow*)(w);
    if (currentPlayer == blackPlayer) {
        currentPlayer = whitePlayer;
        W->messageLabel->setText("Ходят белые");
    }
    else {
        currentPlayer = blackPlayer;
        W->messageLabel->setText("Ходят черные");
    }
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

bool Chessboard::checkMove(QPoint from, QPoint to) {
    if (squares[to.y()][to.x()]->piece!=nullptr && squares[to.y()][to.x()]->piece->color == squares[from.y()][from.x()]->piece->color)
        return false;
    if (to == from)
        return false;
    Piece *piece = squares[from.y()][from.x()]->piece;
    if (piece->type == Piece::rook) {
        if (to.x()!=from.x() && to.y()!=from.y())
            return false;
        if (to.x() == from.x()) {
            int fromY = min(to.y(), from.y());
            int toY = max(to.y(), from.y());
            for (int i = fromY + 1; i<toY; i++)
                if (squares[i][to.x()]->piece!=nullptr)
                    return false;
        }
        else {
            int fromX = min(to.x(), from.x());
            int toX = max(to.x(), from.x());
            for (int i = fromX + 1; i<toX; i++)
                if (squares[to.y()][i]->piece!=nullptr)
                    return false;
        }
    }
    if (piece->type == Piece::knight) {
        if (abs((from.x()-to.x()) * (from.y() - to.y())) != 2)
            return false;
    }
    if (piece->type == Piece::bishop) {

    }
    if (piece->type == Piece::queen) {

    }
    if (piece->type == Piece::king) {

    }
    if (piece->type == Piece::pawn) {

    }
    return true;
}
