#include "mainwindow.h"
#include <QDebug>

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

    for (int i=0 ;i<10; i++)
        for (int j=0; j<10; j++)
            squares[i][j] = nullptr;

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

    for (int y=1; y<=8; y++)
        for (int x=1; x<=8; x++) {
            squares[y][x] = new Square(x, y, (x+y)%2?Square::black:Square::white);
            board->addItem(squares[y][x]);
        }

}
