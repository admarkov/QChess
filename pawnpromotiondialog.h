#ifndef PAWNPROMOTIONDIALOG_H
#define PAWNPROMOTIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QWidget>

class PawnPromotionDialog : public QDialog
{

public:

    PawnPromotionDialog(QWidget* parent = 0);

    enum PieceType {pawn, rook, knight, bishop, queen, king} chosenPiece;
    enum Color {black, white};

    QPushButton *pawnBtn;
    QPushButton *rookBtn;
    QPushButton *knightBtn;
    QPushButton *bishopBtn;
    QPushButton *queenBtn;

    void setColor(Color clr);

signals:
    void pawnSelected();
    void rookSelected();
    void knightSelected();
    void bishopSelected();
    void queenSelected();

};

#endif // PAWNPROMOTIONDIALOG_H
