#include "chessboard.h"
#include "mainwindow.h"
#include <algorithm>
#include <QDebug>
#include <QMessageBox>

using namespace std;

Chessboard::Chessboard(QObject *parent)
    : QGraphicsScene(parent)
{
    w = parent;

    MainWindow *W = dynamic_cast<MainWindow*>(w);

    ppd = new PawnPromotionDialog(dynamic_cast<QWidget*>(w));
    connect(ppd->rookBtn, SIGNAL(clicked(bool)), W, SLOT(pawnToRook()));
    connect(ppd->knightBtn, SIGNAL(clicked(bool)), W, SLOT(pawnToKnight()));
    connect(ppd->bishopBtn, SIGNAL(clicked(bool)), W, SLOT(pawnToBishop()));
    connect(ppd->queenBtn, SIGNAL(clicked(bool)), W, SLOT(pawnToQueen()));

    for (int i=0 ;i<10; i++)
        for (int j=0; j<10; j++)
            squares[i][j] = nullptr;

    for (int y=1; y<=8; y++)
        for (int x=1; x<=8; x++) {
            squares[y][x] = new Square(x, y, (x+y)%2?Square::black:Square::white);
            addItem(squares[y][x]);
        }

    restoreGame();

}

void Chessboard::toggleMove() {
    MainWindow *W = (MainWindow*)(w);
    if (currentPlayer == blackPlayer) {
        currentPlayer = whitePlayer;
        if (isCheckmate()) {
            stopGame("Мат! Выиграли черные.");
            return;
        }
        if (isCheck())
            W->messageLabel->setText("Ходят белые. Шах!");
        else
            W->messageLabel->setText("Ходят белые");
    }
    else {
        currentPlayer = blackPlayer;
        if (isCheckmate()) {
            stopGame("Мат! Выиграли белые.");
            return;
        }
        if (isCheck())
            W->messageLabel->setText("Ходят черные. Шах!");
        else
            W->messageLabel->setText("Ходят черные");
    }

    if (isLeftCastlingAble()) {
        W->castlingLeftBtn->setEnabled(true);
    }
    else {
        W->castlingLeftBtn->setEnabled(false);
    }

    if (isRightCastlingAble()) {
        W->castlingRightBtn->setEnabled(true);
    }
    else {
        W->castlingRightBtn->setEnabled(false);
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

bool Chessboard::checkMove(QPoint from, QPoint to, bool forCheckCheck) {
    GodsHelp();
    if (squares[from.y()][from.x()]->piece == nullptr)
        return false;
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
        if (abs(from.x()-to.x())!=abs(from.y()-to.y()))
            return false;
        if (from.x() < to.x() && from.y() < to.y() || from.x() > to.x() && from.y() > to.y()) {
            int fromX = min(to.x(), from.x());
            int fromY = min(to.y(), from.y());
            int toX = max(to.x(), from.x());
            int toY = max(to.y(), from.y());
            for (int i=1; i<toX - fromX; i++)
                if (squares[fromY+i][fromX+i]->piece!=nullptr)
                    return false;
        }
        else {
            int fromX = min(to.x(), from.x());
            int fromY = max(to.y(), from.y());
            int toX = max(to.x(), from.x());
            int toY = min(to.y(), from.y());
            for (int i=1; i<toX - fromX; i++)
                if (squares[fromY-i][fromX+i]->piece!=nullptr)
                    return false;
        }
    }
    if (piece->type == Piece::queen) {
        if (to.x()-from.x() == 0) {
            int fromY = min(to.y(), from.y());
            int toY = max(to.y(), from.y());
            for (int i = fromY + 1; i<toY; i++)
                if (squares[i][to.x()]->piece!=nullptr)
                    return false;
        }
        else if (to.y() - from.y() == 0) {
            int fromX = min(to.x(), from.x());
            int toX = max(to.x(), from.x());
            for (int i = fromX + 1; i<toX; i++)
                if (squares[to.y()][i]->piece!=nullptr)
                    return false;
        }
        else if (to.x()-from.x() == to.y()-from.y()) {
            int fromX = min(to.x(), from.x());
            int fromY = min(to.y(), from.y());
            int toX = max(to.x(), from.x());
            int toY = max(to.y(), from.y());
            for (int i=1; i<toX - fromX; i++)
                if (squares[fromY+i][fromX+i]->piece!=nullptr)
                    return false;
        }
        else if (from.x()-to.x() == to.y() - from.y()) {
            int fromX = min(to.x(), from.x());
            int fromY = max(to.y(), from.y());
            int toX = max(to.x(), from.x());
            int toY = min(to.y(), from.y());
            for (int i=1; i<toX - fromX; i++)
                if (squares[fromY-i][fromX+i]->piece!=nullptr)
                    return false;
        }
        else
            return false;
    }
    if (piece->type == Piece::king) {
        if (abs(from.x()-to.x())>1 || abs(from.y()-to.y())>1)
            return false;
    }
    if (piece->type == Piece::pawn) {
        if (abs((from.x()-to.x())*(from.y()-to.y())) == 1) {
            if (squares[to.y()][to.x()]->piece==nullptr)
                return false;
            if (squares[to.y()][to.x()]->piece->color == piece->color)
                return false;
            if (piece->color==Piece::black && from.y() > to.y())
                return false;
            if (piece->color==Piece::white && from.y() < to.y())
                return false;
        }
        else {
            if (to.x()!=from.x())
                return false;
            if (piece->color == Piece::black) {
                if (squares[to.y()][to.x()]->piece!=nullptr || !(to.y()-from.y()==1 || to.y()-from.y()==2 && from.y()==2 && squares[3][from.x()]->piece==nullptr))
                    return false;
            }
            else {
                if (squares[to.y()][to.x()]->piece!=nullptr || !(to.y()-from.y()==-1 || to.y()-from.y()==-2 && from.y()==7 && squares[6][from.x()]->piece==nullptr))
                    return false;
            }
        }
    }
    if (!forCheckCheck) {
        bool good = true;
        bool wasCheck = isCheckNow;
        Piece *fromBefore = squares[from.y()][from.x()]->piece;
        Piece *toBefore = squares[to.y()][to.x()]->piece;
        squares[to.y()][to.x()]->piece = fromBefore;
        squares[from.y()][from.x()]->piece = nullptr;
        if (isCheck())
            good = false;
        squares[to.y()][to.x()]->piece = toBefore;
        squares[from.y()][from.x()]->piece = fromBefore;
        isCheckNow = wasCheck;
        return good;
    }
    return true;
}

bool Chessboard::isCheck() {
    GodsHelp();
    for (int i=1; i<=8; i++)
        for (int j=1; j<=8; j++) {
            if (squares[i][j]->piece!=nullptr && squares[i][j]->piece->color != currentPlayer) {
                for (int ii=1; ii<=8; ii++)
                    for (int jj=1; jj<=8; jj++) {
                        if (squares[ii][jj]->piece != nullptr && squares[ii][jj]->piece->color==currentPlayer && squares[ii][jj]->piece->type == Piece::king && checkMove(QPoint(j,i), QPoint(jj, ii), true))
                            return isCheckNow = true;
                    }
            }
        }
    return isCheckNow = false;
}

bool Chessboard::isCheckmate() {
    GodsHelp();
    for (int i=1; i<=8; i++)
        for (int j=1; j<=8; j++) {
            if (squares[i][j]->piece!=nullptr && squares[i][j]->piece->color == currentPlayer) {
                for (int ii=1; ii<=8; ii++)
                    for (int jj=1; jj<=8; jj++) {
                        {
                            if (checkMove(QPoint(j, i), QPoint(jj, ii), true)) {
                                bool good = false;
                                QPoint from(j,i);
                                QPoint to(jj, ii);
                                Piece *fromBefore = squares[from.y()][from.x()]->piece;
                                Piece *toBefore = squares[to.y()][to.x()]->piece;
                                squares[to.y()][to.x()]->piece = fromBefore;
                                squares[from.y()][from.x()]->piece = nullptr;
                                if (!isCheck())
                                    good = true;
                                squares[to.y()][to.x()]->piece = toBefore;
                                squares[from.y()][from.x()]->piece = fromBefore;
                                if (good)
                                    return false;
                            }
                        }
                    }
            }
        }
    return true;
}

void Chessboard::restoreSquares() {
    for (int i=1; i<=8; i++)
        for (int j=1; j<=8; j++) {
            if (squares[i][j]->color == Square::black)
                squares[i][j]->setBrush(QBrush(QColor("#78785a")));
            else
                squares[i][j]->setBrush(QBrush(QColor("#d3d39e")));
        }
}

void Chessboard::restoreGame() {
    isCheckNow = false;
    draggingPiece = nullptr;
    currentPlayer = blackPlayer;
    noBlackLeftCastling = noBlackRightCastling = false;
    noWhiteLeftCastling = noWhiteRightCastling = false;

    for (int i=1; i<=8; i++)
        for (int j=1; j<=8; j++)
            if (squares[i][j]->piece!=nullptr) {
                removeItem(squares[i][j]->piece);
                delete squares[i][j]->piece;
                squares[i][j]->piece = nullptr;
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

void Chessboard::stopGame(QString message) {
    QMessageBox::information(dynamic_cast<QWidget*>(this),
                           QString("Игра окончена"),
                           message);
    restoreGame();
}

bool Chessboard::checkCastlingPosition(int x, int y) {
    squares[y][x]->piece = new Piece(currentPlayer == whitePlayer ? Piece::white : Piece::black, Piece::king);
    bool verdict = !isCheck();
    delete squares[y][x]->piece;
    squares[y][x]->piece = nullptr;
    return verdict;
}

bool Chessboard::isLeftCastlingAble() {
    if (currentPlayer == whitePlayer) {
        if (noWhiteLeftCastling)
            return false;
        if (squares[8][2]->piece!=nullptr || squares[8][3]->piece!=nullptr || squares[8][4]->piece!=nullptr)
            return false;
        if (checkCastlingPosition(2,8) && checkCastlingPosition(3,8) && checkCastlingPosition(4,8))
            return true;
        return false;
    }
    else {
        if (noBlackLeftCastling)
            return false;
        if (squares[1][2]->piece!=nullptr || squares[1][3]->piece!=nullptr || squares[1][4]->piece!=nullptr)
            return false;
        if (checkCastlingPosition(2,1) && checkCastlingPosition(3,1) && checkCastlingPosition(4,1))
            return true;
        return false;
    }
}

void Chessboard::leftCastling() {
    if (currentPlayer == whitePlayer) {
        squares[8][3]->piece = squares[8][5]->piece;
        squares[8][5]->piece = nullptr;
        squares[8][3]->piece->setPos(80*2, 80*7);
        squares[8][4]->piece = squares[8][1]->piece;
        squares[8][1]->piece = nullptr;
        squares[8][4]->piece->setPos(80*3, 80*7);
        noWhiteLeftCastling = noWhiteRightCastling = true;
    }
    else {
        squares[1][3]->piece = squares[1][5]->piece;
        squares[1][5]->piece = nullptr;
        squares[1][3]->piece->setPos(80*2, 0);
        squares[1][4]->piece = squares[1][1]->piece;
        squares[1][1]->piece = nullptr;
        squares[1][4]->piece->setPos(80*3, 0);
        noBlackLeftCastling = noBlackRightCastling = true;
    }
    toggleMove();
}

bool Chessboard::isRightCastlingAble() {
    if (currentPlayer == whitePlayer) {
        if (noWhiteLeftCastling)
            return false;
        if (squares[8][6]->piece!=nullptr || squares[8][7]->piece!=nullptr)
            return false;
        if (checkCastlingPosition(6,8) && checkCastlingPosition(7,8))
            return true;
        return false;
    }
    else {
        if (noBlackLeftCastling)
            return false;
        if (squares[1][6]->piece!=nullptr || squares[1][7]->piece!=nullptr)
            return false;
        if (checkCastlingPosition(6,1) && checkCastlingPosition(7,1))
            return true;
        return false;
    }
}

void Chessboard::rightCastling() {
    if (currentPlayer == whitePlayer) {
        squares[8][7]->piece = squares[8][5]->piece;
        squares[8][5]->piece = nullptr;
        squares[8][7]->piece->setPos(80*6, 80*7);
        squares[8][6]->piece = squares[8][8]->piece;
        squares[8][8]->piece = nullptr;
        squares[8][6]->piece->setPos(80*5, 80*7);
        noWhiteLeftCastling = noWhiteRightCastling = true;
    }
    else {
        squares[1][7]->piece = squares[1][5]->piece;
        squares[1][5]->piece = nullptr;
        squares[1][7]->piece->setPos(80*6, 0);
        squares[1][6]->piece = squares[1][8]->piece;
        squares[1][8]->piece = nullptr;
        squares[1][6]->piece->setPos(80*5, 0);
        noBlackLeftCastling = noBlackRightCastling = true;
    }
    toggleMove();
}

void Chessboard::pawnToRook() {
    removeItem(squares[pawnY][pawnX]->piece);
    delete squares[pawnY][pawnX]->piece;
    squares[pawnY][pawnX]->piece = new Piece(currentPlayer == whitePlayer ? Piece::white : Piece::black, Piece::rook);
    addItem(squares[pawnY][pawnX]->piece);
    squares[pawnY][pawnX]->piece->setPos(pawnX*80-80, pawnY*80-80);
}

void Chessboard::pawnToKnight() {
    removeItem(squares[pawnY][pawnX]->piece);
    delete squares[pawnY][pawnX]->piece;
    squares[pawnY][pawnX]->piece = new Piece(currentPlayer == whitePlayer ? Piece::white : Piece::black, Piece::knight);
    addItem(squares[pawnY][pawnX]->piece);
    squares[pawnY][pawnX]->piece->setPos(pawnX*80-80, pawnY*80-80);
}


void Chessboard::pawnToBishop() {
    removeItem(squares[pawnY][pawnX]->piece);
    delete squares[pawnY][pawnX]->piece;
    squares[pawnY][pawnX]->piece = new Piece(currentPlayer == whitePlayer ? Piece::white : Piece::black, Piece::bishop);
    addItem(squares[pawnY][pawnX]->piece);
    squares[pawnY][pawnX]->piece->setPos(pawnX*80-80, pawnY*80-80);
}

void Chessboard::pawnToQueen() {
    removeItem(squares[pawnY][pawnX]->piece);
    delete squares[pawnY][pawnX]->piece;
    squares[pawnY][pawnX]->piece = new Piece(currentPlayer == whitePlayer ? Piece::white : Piece::black, Piece::queen);
    addItem(squares[pawnY][pawnX]->piece);
    squares[pawnY][pawnX]->piece->setPos(pawnX*80-80, pawnY*80-80);
}


void Chessboard::GodsHelp() {
    /*
.______________________________________________.
| [~~-__]        _______         [~~-__]       |
| . . .-,    _-~~       ~~-_     .-,    ,      |
| |Y| |-' _-~    _______    ~-_  +-+ \ /       |
| ` ' '  /    _zZ=zzzzz=Zz_    \ `-'  6        |
|       /    // /~    *~\ \\    \              |
|      f    ff f _-zzz--_] ??    ?     -- --   |
|      |    || L/ -=6,)_--L|j    |     IC XC   |
|      |    ||/f     //`9=-7    _L-----__      |
|      t    |( |    </   //  _-~ _____/o 7-_   |
|       \   | )t   --_ ,'/  /w~-<_____ ~Y   \  |
|        \  |( |\_   _/ f  f~-_f_   __\  ?   ? |
|         ~-j \|  ~~~\ /|  |   `6) 6=-'? |   | |
|       __-~   \______Y |_-|   f<      t |   | |
|    _zZ   *    \    /  /  t   t =    / \j~-_j |
|  ,'   ~-_     _\__/__/_   \   >-r--~  J-_N/  |
| /f       T\  ( )_______)   ~-<  L   ,' \-~   |
|f |       | \  \Cyg npa\___---~~7 ~~~ ___T\   |
f| |       | |T\ \BegeHz \      /     /   ) \  |
|| |       | || ~\\cygumc--_   f     /   /|  \ |
|| |_______| ||   ~\mu^oE__ \_r^--__<~- / j   ?|
|| /       \ j|     \u wegp\__|    | \ / /    ||
|f/~~~~~~~-zZ_L_.   _\_______\`_     _/ /|    ||
|Y  ,     ff    |~~T--_/~       ~---~  / j    ||
||f t     jj    |  |(  \   ~-r______--~ /     t|
|t|  \___//_____|~~~7\  \   f ff    _--~       ?
| Y    ,'/    _<   /  \\\\  | jj   / ~-_       |
| |   / f c-~~  ~-<____UUU--~~~_--~     \      |
|_|__f__|__````-----'_________/__________?_____|
     */
}

