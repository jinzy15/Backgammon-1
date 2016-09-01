#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QSignalMapper>
#include <QTcpSocket>

connectDialog::connectDialog(MainWindow* s,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectDialog)
{
    ui->setupUi(this);
    client=s;
    QSignalMapper* mapper = new QSignalMapper(this);
    connect(ui->num0, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num0, "0");
    connect(ui->num1, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num1, "1");
    connect(ui->num2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num2, "2");
    connect(ui->num3, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num3, "3");
    connect(ui->num4, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num4, "4");
    connect(ui->num5, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num5, "5");
    connect(ui->num6, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num6, "6");
    connect(ui->num7, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num7, "7");
    connect(ui->num8, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num8, "8");
    connect(ui->num9, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->num9, "9");
    connect(ui->dot, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->dot, ".");
    connect(mapper, SIGNAL(mapped(const QString&)), this, SLOT(displayed(const QString&)));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->del,SIGNAL(clicked()),this,SLOT(del()));
    connect(ui->ok,SIGNAL(clicked()),this,SLOT(ok()));
}
void connectDialog::displayed(const QString& a){
    string+=a;
    ui->lineEdit->setText(string);
}
void connectDialog::del(){
    string = string.left(string.length() - 1);
    ui->lineEdit->setText(string);
}
void connectDialog::ok(){
    client->readWriteSocket = new QTcpSocket;
    //str=string;
    client->readWriteSocket->connectToHost(QHostAddress(string),8888);
    QObject::connect(client->readWriteSocket,SIGNAL(readyRead()),client,SLOT(recvMessage()));
    client->flag=false;
    this->close();
}
connectDialog::~connectDialog()
{
    delete ui;
}
