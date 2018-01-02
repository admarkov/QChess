#include "mainwindow.h"
#include <QDebug>
#include "piece.h"

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

    this->setFixedSize(w, h+20);

    messageLabel = new QLabel(this);
    messageLabel->setGeometry(5, h, 400, 20);

    centralWidget = new QWidget(this);
    centralWidget->setGeometry(0, 0, w, h+20);

    board = new Chessboard(this);
    board->setSceneRect(0, 0, w, h);

    view = new QGraphicsView(centralWidget);
    view->setGeometry(0, 0, w, h);
    view->setScene(board);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->viewport()->setAcceptDrops(true);

    //QPushButton *castlingBtn;
    //QLabel *messageLabel;

    castlingLeftBtn = new QPushButton(this);
    castlingLeftBtn->setText("◀ Рокировка");
    castlingLeftBtn->setEnabled(false);
    castlingLeftBtn->setGeometry(w - 2*castlingLeftBtn->width(), h - 4, castlingLeftBtn->width()+4, castlingLeftBtn->height());

    castlingRightBtn = new QPushButton(this);
    castlingRightBtn->setText("Рокировка ▶");
    castlingRightBtn->setEnabled(false);
    castlingRightBtn->setGeometry(w - castlingRightBtn->width(), h - 4, castlingRightBtn->width()+4, castlingRightBtn->height());

    drawBtn = new QPushButton(this);
    drawBtn->setText("Ничья");
    drawBtn->setGeometry(w - 3*castlingRightBtn->width() + 8, h - 4, castlingRightBtn->width()+4, castlingRightBtn->height());
    connect(drawBtn, SIGNAL(clicked(bool)), this, SLOT(draw()));

}

void MainWindow::draw() {
    board->stopGame("Ничья.");
}
