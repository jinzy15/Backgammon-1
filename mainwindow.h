#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include "dialog.h"
#include "connectdialog.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QVector>

namespace Ui {
class MainWindow;
}
class Dialog;
class connectDialog;

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
    QVector<int>danger_x;
    QVector<int>danger_y;
    QTcpSocket *readWriteSocket;
    QTcpServer  *listenSocket;
    bool flag=true;
    void danger_judge();

    Dialog* creatDialog;
    connectDialog* connectDialog;
    bool not_contain_self(int ,int);
    bool not_contain_other(int ,int);

private:
    Ui::MainWindow *ui;

public slots:
    void showCreateDialog();
    void showConnectDialog();
    void initServer();
    void acceptConnection();
    void recvMessage();
    void sendMessage(int ,int );
};

#endif // MAINWINDOW_H
