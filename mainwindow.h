#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void checkWin(int x,int y);
    void winShow(int colorCenter);
    void tie();

    int xPressed;
    int yPressed;
    int numCounts;
    int counts[225][3];//0表示x   1表示y    2表示颜色
    int checkBoard[15][15];//模拟棋盘，1表示黑色，-1表示白色

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
