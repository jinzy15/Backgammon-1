#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    this->setMaximumHeight(640);
    this->setMinimumHeight(640);
    this->setMaximumSize(640,640);
    this->setMinimumSize(640,640);
    ui->setupUi(this);

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
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent)
{
    int x = int(float(mouseEvent->x())/40+0.5)*40;
    int y = int(float(mouseEvent->y())/40+0.5)*40;

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
        checkWin(x,y);
        this->update();      //用于绘图
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
