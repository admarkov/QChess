#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QPushButton>
#include "chessboard.h"
#include "square.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    const int h=640, w=640;

    QWidget *centralWidget;

    Chessboard *board;
    QGraphicsView *view;

    QPushButton *castlingLeftBtn;
    QPushButton *castlingRightBtn;
    QPushButton *drawBtn;
    QLabel *messageLabel;

private:
    void setupUI();

public slots:
    void draw();
    void leftCastling();
    void rightCastling();

    void pawnToRook();
    void pawnToKnight();
    void pawnToBishop();
    void pawnToQueen();
};

#endif // MAINWINDOW_H
