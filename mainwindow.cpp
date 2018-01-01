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

    castlingBtn = new QPushButton(this);
    castlingBtn->setText("Рокировка");
    castlingBtn->setEnabled(false);
    castlingBtn->setGeometry(w - castlingBtn->width(), h - 4, castlingBtn->width()+4, castlingBtn->height());

}
