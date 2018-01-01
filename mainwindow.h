#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QGraphicsView>
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

private:
    void setupUI();
};

#endif // MAINWINDOW_H
