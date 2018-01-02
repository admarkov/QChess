#include "pawnpromotiondialog.h"
#include <QDebug>
#include <QSize>

PawnPromotionDialog::PawnPromotionDialog(QWidget* parent)
    :QDialog(parent)
{

    setFixedSize(460,100);
    setWindowTitle("Выберите фигуру, на которую будет заменена пешка");

    chosenPiece = pawn;

    pawnBtn = new QPushButton(this);
    rookBtn = new QPushButton(this);
    knightBtn = new QPushButton(this);
    bishopBtn = new QPushButton(this);
    queenBtn = new QPushButton(this);

    pawnBtn->setIconSize(QSize(80,80));
    rookBtn->setIconSize(QSize(80,80));
    bishopBtn->setIconSize(QSize(80,80));
    knightBtn->setIconSize(QSize(80,80));
    queenBtn->setIconSize(QSize(80,80));

    pawnBtn->setGeometry(10,10,80,80);
    rookBtn->setGeometry(100,10,80,80);
    knightBtn->setGeometry(190,10,80,80);
    bishopBtn->setGeometry(280,10,80,80);
    queenBtn->setGeometry(370,10,80,80);

    connect(pawnBtn, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(rookBtn, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(knightBtn, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(bishopBtn, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(queenBtn, SIGNAL(clicked(bool)), this, SLOT(accept()));

}

void PawnPromotionDialog::setColor(Color clr) {

    if (clr == white)
        pawnBtn->setIcon(QPixmap(":/Images/pawn_white.svg"));
    else
        pawnBtn->setIcon(QPixmap(":/Images/pawn_black.svg"));

    if (clr == white)
        rookBtn->setIcon(QPixmap(":/Images/rook_white.svg"));
    else
        rookBtn->setIcon(QPixmap(":/Images/rook_black.svg"));

    if (clr == white)
        knightBtn->setIcon(QPixmap(":/Images/knight_white.svg"));
    else
        knightBtn->setIcon(QPixmap(":/Images/knight_black.svg"));

    if (clr == white)
        bishopBtn->setIcon(QPixmap(":/Images/bishop_white.svg"));
    else
        bishopBtn->setIcon(QPixmap(":/Images/bishop_black.svg"));

    if (clr == white)
        queenBtn->setIcon(QPixmap(":/Images/queen_white.svg"));
    else
        queenBtn->setIcon(QPixmap(":/Images/queen_black.svg"));
}
