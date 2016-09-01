#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->xPressed = 0;
    this->yPressed = 0;
    this->numCounts = 0;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            checkBoard[i][j] = 0;
        }
    }
//    this->setMaximumHeight(640);
//    this->setMinimumHeight(640);
//    this->setMaximumSize(640,640);
//    this->setMinimumSize(640,640);
    ui->setupUi(this);
    connect(ui->createButton,SIGNAL(clicked()),this,SLOT(showCreateDialog()));
    connect(ui->connectButton,SIGNAL(clicked()),this,SLOT(showConnectDialog()));
    connect(ui->quitButton,SIGNAL(clicked()),this,SLOT(close()));

//    readWriteSocket=new QTcpSocket();
//    listenSocket=new QTcpServer();

}
void MainWindow::showCreateDialog(){
    qDebug()<<"show create";
     creatDialog=new Dialog(this);
        creatDialog->show();

}
void MainWindow::showConnectDialog(){
    qDebug()<<"show connect";
   connectDialog=new class connectDialog(this);
   connectDialog->show();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    //画线
    for(int i=40;i<640;)
    {
        QPoint pointOne(40,i);
        QPoint pointTwo(600,i);
        painter.drawLine(pointOne,pointTwo);
        i = i + 40;
    }
    for(int i=40;i<640;)
    {
        QPoint pointOne(i,40);
        QPoint pointTwo(i,600);
        painter.drawLine(pointOne,pointTwo);
        i = i + 40;
    }
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for(int i=0;i<this->numCounts;i++)
    {

        if(i%2 == 0)
        {
            brush.setColor(Qt::black);
        }
        else
        {
            brush.setColor(Qt::white);
        }
        painter.setBrush(brush);
        painter.drawEllipse(this->counts[i][0]-16,this->counts[i][1]-16,32,32);//画圆函数的特殊性。找左上角，所以也可以画椭圆
    }
//    for (int i = 0; i < danger_x.size(); i++)
//        {
//            QImage bomb("C:\\Users\\Starry Sky\\Desktop\\myGobang\\Gobang6\\myGobang_client6\\Bomb.png");
//            QImage nbomb = bomb.scaled(reclongnes,reclongnes,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//            p->setPen(QPen(Qt::red));
//            p->drawImage(height()/10+(danger_x[i]-1)*reclongnes-reclong/(lines*2),height()/10+(danger_y[i]-1)*reclongnes-reclong/(lines*2),nbomb);
//        }
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent)
{
    int x = int(float(mouseEvent->x())/40+0.5)*40;
    int y = int(float(mouseEvent->y())/40+0.5)*40;

    //按下的位置在棋盘内
    if((flag&&this->numCounts%2 == 0)||(!flag&&this->numCounts%2 == 1))
    {if(x>0&&x<640&&y>0&&y<640&&this->checkBoard[y/40-1][x/40-1]==0)//当前按键位置在棋盘内并且当前位置没有棋子
    {
        sendMessage(x,y);
        this->numCounts += 1;//棋子数目加一
        if(this->numCounts%2 != 0)//棋局矩阵构造
        {
            this->checkBoard[y/40-1][x/40-1] = 1; //1表示黑色
        }
        else
        {
            this->checkBoard[y/40-1][x/40-1] = -1;//-1表示白色
        }
        this->counts[this->numCounts-1][0] = x;
        this->counts[this->numCounts-1][1] = y;
        this->counts[this->numCounts-1][2] = this->numCounts%2;
        this->update();
        checkWin(x,y);

        //用于绘图
    }
    }

}//x  y为需要加入棋子的圆心位置。。。逻辑结构为   从棋盘数据中找出是否有子。   没有加入到两个数据结构中。根据下棋数判断黑白  并重绘画图。并判断能否胜出。
//flag为真证明下的是黑棋，否则下的是白棋


void MainWindow::initServer()
{
    this->listenSocket=new QTcpServer();
    this->listenSocket->listen(QHostAddress::Any,8888);
    QObject::connect(this->listenSocket,SIGNAL(newConnection()),this,SLOT(acceptConnection()));

}

void MainWindow::acceptConnection()
{
    this->readWriteSocket =this->listenSocket->nextPendingConnection();
    flag=true;
    QMessageBox::information(NULL, tr("Complete!"), tr("Connect successfully."), QMessageBox::Ok);
    QObject::connect(this->readWriteSocket,SIGNAL(readyRead()),this,SLOT(recvMessage()));
}

void MainWindow::sendMessage(int x, int y)
{
    QByteArray array;
    array.clear();
    array.append(QString::number(x)+"/"+QString::number(y));
    this->readWriteSocket->write(array);
}
void MainWindow::recvMessage()
{
    //qDebug() << "server222222222222222222222222";
    QString posstring;
    posstring = this->readWriteSocket->readAll();
    int m;
    QString xx,yy;
    for (int i = 0; i < posstring.size(); i++)
        if ( posstring[i] == '/' ) m = i;
    xx.clear();yy.clear();
    for (int i = 0; i < m; i++) xx += posstring[i];
    for (int i = m+1; i < posstring.size(); i++) yy += posstring[i];


    int x = xx.toInt();
    int y = yy.toInt();

    //按下的位置在棋盘内
    if(x>0&&x<640&&y>0&&y<640&&this->checkBoard[y/40-1][x/40-1]==0)//当前按键位置在棋盘内并且当前位置没有棋子
    {
        this->numCounts += 1;//棋子数目加一
        if(this->numCounts%2 != 0)//棋局矩阵构造
        {
            this->checkBoard[y/40-1][x/40-1] = 1; //1表示黑色
        }
        else
        {
            this->checkBoard[y/40-1][x/40-1] = -1;//-1表示白色
        }
        this->counts[this->numCounts-1][0] = x;
        this->counts[this->numCounts-1][1] = y;
        this->counts[this->numCounts-1][2] = this->numCounts%2;
        this->update();
        checkWin(x,y);
             //用于绘图
    }

}//x  y为需要加入棋子的圆心位置。。。逻辑结构为   从棋盘数据中找出是否有子。   没有加入到两个数据结构中。根据下棋数判断黑白  并重绘画图。并判断能否胜出。








void MainWindow::checkWin(int x, int y)
{
    int row = y/40-1; //显示第几行
    int col = x/40-1; //显示第几列
    int colorCenter = this->checkBoard[row][col];//中间点的颜色
    ///////////列
    if(row>=4&&this->checkBoard[row-4][col]==colorCenter&&this->checkBoard[row-3][col]==colorCenter&&this->checkBoard[row-2][col]==colorCenter&&this->checkBoard[row-1][col]==colorCenter)
    {//该点上面
        winShow(colorCenter);
    }
    else if(row>=3&&row<=13&&this->checkBoard[row+1][col]==colorCenter&&this->checkBoard[row-3][col]==colorCenter&&this->checkBoard[row-2][col]==colorCenter&&this->checkBoard[row-1][col]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(row>=2&&row<=12&&this->checkBoard[row+2][col]==colorCenter&&this->checkBoard[row+1][col]==colorCenter&&this->checkBoard[row-2][col]==colorCenter&&this->checkBoard[row-1][col]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(row>=1&&row<=11&&this->checkBoard[row+3][col]==colorCenter&&this->checkBoard[row+2][col]==colorCenter&&this->checkBoard[row+1][col]==colorCenter&&this->checkBoard[row-1][col]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(row<=10&&this->checkBoard[row+4][col]==colorCenter&&this->checkBoard[row+3][col]==colorCenter&&this->checkBoard[row+2][col]==colorCenter&&this->checkBoard[row+1][col]==colorCenter)
    {//该点下面
        winShow(colorCenter);
    }
    //////////行
    else if(col>=4&&this->checkBoard[row][col-4]==colorCenter&&this->checkBoard[row][col-3]==colorCenter&&this->checkBoard[row][col-2]==colorCenter&&this->checkBoard[row][col-1]==colorCenter)
    {//该点左边
        winShow(colorCenter);
    }
    else if(col>=3&&col<=13&&this->checkBoard[row][col+1]==colorCenter&&this->checkBoard[row][col-3]==colorCenter&&this->checkBoard[row][col-2]==colorCenter&&this->checkBoard[row][col-1]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(col>=2&&col<=12&&this->checkBoard[row][col+2]==colorCenter&&this->checkBoard[row][col+1]==colorCenter&&this->checkBoard[row][col-2]==colorCenter&&this->checkBoard[row][col-1]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(col>=1&&col<=11&&this->checkBoard[row][col+3]==colorCenter&&this->checkBoard[row][col+2]==colorCenter&&this->checkBoard[row][col+1]==colorCenter&&this->checkBoard[row][col-1]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(col<=10&&this->checkBoard[row][col+4]==colorCenter&&this->checkBoard[row][col+3]==colorCenter&&this->checkBoard[row][col+2]==colorCenter&&this->checkBoard[row][col+1]==colorCenter)
    {//该点右边
        winShow(colorCenter);
    }
    //////////左上到右下
    else if(row>=4&&col>=4&&this->checkBoard[row-4][col-4]==colorCenter&&this->checkBoard[row-3][col-3]==colorCenter&&this->checkBoard[row-2][col-2]==colorCenter&&this->checkBoard[row-1][col-1]==colorCenter)
    {//该点左上
        winShow(colorCenter);
    }
    else if(row>=3&&col>=3&&row<=13&&col<=13&&this->checkBoard[row+1][col+1]==colorCenter&&this->checkBoard[row-3][col-3]==colorCenter&&this->checkBoard[row-2][col-2]==colorCenter&&this->checkBoard[row-1][col-1]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(row>=2&&col>=2&&row<=12&&col<=12&&this->checkBoard[row+2][col+2]==colorCenter&&this->checkBoard[row+1][col+1]==colorCenter&&this->checkBoard[row-2][col-2]==colorCenter&&this->checkBoard[row-1][col-1]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(row>=1&&col>=1&&row<=11&&col<=11&&this->checkBoard[row+3][col+3]==colorCenter&&this->checkBoard[row+2][col+2]==colorCenter&&this->checkBoard[row+1][col+1]==colorCenter&&this->checkBoard[row-1][col-1]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(row<=10&&col<=10&&this->checkBoard[row+4][col+4]==colorCenter&&this->checkBoard[row+3][col+3]==colorCenter&&this->checkBoard[row+2][col+2]==colorCenter&&this->checkBoard[row+1][col+1]==colorCenter)
    {//该点右下
        winShow(colorCenter);
    }
    /////////右上到左下
    else if(row>=4&&col<=10&&this->checkBoard[row-4][col+4]==colorCenter&&this->checkBoard[row-3][col+3]==colorCenter&&this->checkBoard[row-2][col+2]==colorCenter&&this->checkBoard[row-1][col+1]==colorCenter)
    {//该点左下
        winShow(colorCenter);
    }
    else if(row>=3&&col<=11&&row<=13&&col>=1&&this->checkBoard[row+1][col-1]==colorCenter&&this->checkBoard[row-3][col+3]==colorCenter&&this->checkBoard[row-2][col+2]==colorCenter&&this->checkBoard[row-1][col+1]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(row>=2&&col<=12&&row<=12&&col>=2&&this->checkBoard[row+2][col-2]==colorCenter&&this->checkBoard[row+1][col-1]==colorCenter&&this->checkBoard[row-2][col+2]==colorCenter&&this->checkBoard[row-1][col+1]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(row>=1&&col<=13&&row<=11&&col>=3&&this->checkBoard[row+3][col-3]==colorCenter&&this->checkBoard[row+2][col-2]==colorCenter&&this->checkBoard[row+1][col-1]==colorCenter&&this->checkBoard[row-1][col+1]==colorCenter)
    {
        winShow(colorCenter);
    }
    else if(row<=4&&col>=4&&this->checkBoard[row+4][col-4]==colorCenter&&this->checkBoard[row+3][col-3]==colorCenter&&this->checkBoard[row+2][col-2]==colorCenter&&this->checkBoard[row+1][col-1]==colorCenter)
    {//该点右上
        winShow(colorCenter);
    }
    else if(numCounts==225)
    {
        tie();
    }
}

void MainWindow::winShow(int colorCenter)
{
    QString infoShow;
    if(colorCenter == 1)//中心点是黑色
    {
        infoShow = "Black Win!";
    }
    else if(colorCenter == -1)
    {
        infoShow = "White Win!";
    }
    if(QMessageBox::information(NULL,"Game Over",infoShow,"Again","Exit")==1)
    {
        close();
    }
    for(int i=0;i<15;i++)//清空棋盘
    {
        for(int j=0;j<15;j++)
        {
            this->checkBoard[i][j]=0;
        }
    }
    this->numCounts = 0;//下子数目为0，即下一个子从黑子开始
}

void MainWindow::tie()
{
    if(QMessageBox::information(NULL,"Game Over","Tie","Again","Exit")==1)
    {
        close();
    }
    for(int i=0;i<15;i++)//清空棋盘
    {
        for(int j=0;j<15;j++)
        {
            this->checkBoard[i][j]=0;
        }
    }
    this->numCounts = 0;//下子数目为0，即下一个子从黑子开始
}
//void MainWindow::danger_judge()
//{
//    QVector<int> xx;
//    QVector<int> yy;
//    QVector<int> num;
//    QVector<int> type;
//    xx.clear();
//    yy.clear();

//    int fx[9] = {0,-1,1,0,0,1,-1,-1,1};
//    int fy[9] = {0,-1,1,-1,1,-1,1,0,0};

//    for (int x = 1; x <= 15; x++)
//        for (int y = 1;  y <= 15; y++)
//            if ( checkBoard[x][y]==0 )
//            {
//                num.clear();
//                type.clear();
//                for (int i = 1; i <= 8; i++)
//                {
//                    int x_next,y_next;
//                    xx.clear();
//                    yy.clear();
//                    xx.append(x);
//                    yy.append(y);
//                    int s=-1,t=0;
//                    while (s<t)
//                    {
//                        s++;
//                        x_next = xx[s] + fx[i];
//                        y_next = yy[s] + fy[i];
//                        if ( !not_contain_other(x_next,y_next) )
//                        {
//                            xx.append(x_next);
//                            yy.append(y_next);
//                            t++;
//                        }
//                    }
//                    if ( xx.size() == 3 && not_contain_self(xx[2] + fx[i],yy[2] + fy[i]) )
//                    {
//                        bool f =true;
//                        if ( !(xx[2] + fx[i] >= 1 && xx[2] + fx[i] <= 15 &&
//                               yy[2] + fy[i] >= 1 && yy[2] + fy[i] <= 15) ) f = false;
//                        int ju;
//                        if ( i % 2 == 0 ) ju = i-1;
//                          else ju = i+1;
//                        if ( !not_contain_self(x + fx[ju],y + fy[ju]) ||
//                              x + fx[ju] <= 0 || x + fx[ju] >= 16 ||
//                              y + fy[ju] <= 0 || y + fy[ju] >= 16 )
//                            f = false;
//                        if ( f )
//                        {
//                            num.append(i);
//                            type.append(3);
//                        }
//                    }
//                    if ( xx.size() == 4 && !not_contain_self(xx[3] + fx[i],yy[3] + fy[i]) )
//                    {
//                        bool f =true;
//                        int ju;
//                        if ( i % 2 == 0 ) ju = i-1;
//                          else ju = i+1;
//                        if (  !not_contain_self(x + fx[ju],y + fy[ju]) ||
//                              x + fx[ju] <= 0 || x + fx[ju] >= 16 ||
//                              y + fy[ju] <= 0 || y + fy[ju] >= 16 )
//                            f = false;
//                        if ( f )
//                        {
//                            num.append(i);
//                            type.append(4);
//                        }
//                    }
//                }
//                if ( num.size() < 2 ) continue;
//                for (int i = 0; i < num.size()-1; i++)
//                    if ( (num[i+1]-num[i] == 1 && (i+1) % 2 == 0 ) || (type[i+1]==4 && type[i] == 4) )
//                    {
//                        num.remove(i+1);
//                        type.remove(i+1);
//                    }
//                if ( num.size() >= 2 ) { danger_x.append(x); danger_y.append(y); }

//            }
//    update();
//}
