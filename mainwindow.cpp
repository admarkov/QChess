#include "mainwindow.h"
#include <QDebug>
#include "piece.h"
#include "pawnpromotiondialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUI() {

    setWindowTitle("QChess");

    this->setFixedSize(w, h+28);

    messageLabel = new QLabel(this);
    messageLabel->setGeometry(5, h+4, 400, 20);

    centralWidget = new QWidget(this);
    centralWidget->setGeometry(0, 0, w, h+20);

    castlingLeftBtn = new QPushButton(this);
    castlingLeftBtn->setText("◀ Рокировка");
    castlingLeftBtn->setEnabled(false);
    castlingLeftBtn->setGeometry(w - 2*castlingLeftBtn->width()-10, h + 2, castlingLeftBtn->width(), castlingLeftBtn->height()-5);
    connect(castlingLeftBtn, SIGNAL(clicked(bool)), this, SLOT(leftCastling()));

    castlingRightBtn = new QPushButton(this);
    castlingRightBtn->setText("Рокировка ▶");
    castlingRightBtn->setEnabled(false);
    castlingRightBtn->setGeometry(w - castlingRightBtn->width() - 5, h + 2, castlingRightBtn->width(), castlingRightBtn->height()-5);
    connect(castlingRightBtn, SIGNAL(clicked(bool)), this, SLOT(rightCastling()));

    board = new Chessboard(this);
    board->setSceneRect(0, 0, w, h);

    view = new QGraphicsView(centralWidget);
    view->setGeometry(0, 0, w, h);
    view->setScene(board);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->viewport()->setAcceptDrops(true);

    drawBtn = new QPushButton(this);
    drawBtn->setText("Ничья");
    drawBtn->setGeometry(w - 3*castlingRightBtn->width() - 15 , h + 2, castlingRightBtn->width(), castlingRightBtn->height());
    connect(drawBtn, SIGNAL(clicked(bool)), this, SLOT(draw()));

}

void MainWindow::draw() {
    board->stopGame("Ничья.");
}

void MainWindow::leftCastling() {
    board->leftCastling();
}

void MainWindow::rightCastling() {
    board->rightCastling();
}

void MainWindow::pawnToRook() {
    board->pawnToRook();
}

void MainWindow::pawnToKnight() {
    board->pawnToKnight();
}


void MainWindow::pawnToBishop() {
    board->pawnToBishop();
}

void MainWindow::pawnToQueen() {
    board->pawnToQueen();
}
