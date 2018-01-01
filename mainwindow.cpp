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

    this->setFixedSize(w,h);

    centralWidget = new QWidget(this);
    centralWidget->setGeometry(0, 0, w, h);

    board = new Chessboard(this);
    board->setSceneRect(0, 0, w, h);

    view = new QGraphicsView(centralWidget);
    view->setGeometry(0, 0, w, h);
    view->setScene(board);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}
