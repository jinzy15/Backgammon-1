#include "dialog.h"
#include "ui_dialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QChar>
#include <QtNetwork>
#include <QDebug>

Dialog::Dialog(MainWindow* window,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->win=window;
    QLabel *label = new QLabel("Host IP:");
    QLineEdit *lineEdit = new QLineEdit(this);
    QString localHostName = QHostInfo::localHostName();
     QHostInfo info = QHostInfo::fromName(localHostName);
     foreach(QHostAddress address, info.addresses())
     {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
        lineEdit->setText(address.toString());
     }
    //const QChar* string = ip_search();
    lineEdit->setReadOnly(true);
    //lineEdit->setText(tr(string));
    QPushButton *ok= new QPushButton(this);
        ok->setText("OK");
    connect(ok,SIGNAL(clicked()),this,SLOT(ok()));
    QPushButton *cancel= new QPushButton(this);
    cancel->setText("Cancel");
    connect(cancel,SIGNAL(clicked()),this,SLOT(cancel()));
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(label,0,0);
    layout->addWidget(lineEdit,0,1);
    layout->addWidget(ok,1,0);
    layout->addWidget(cancel,1,1);
    setLayout(layout);
    this->win->listenSocket=new QTcpServer();
}
void Dialog::ok(){
    qDebug()<<"ok before send";

    this->win->initServer();
    qDebug()<<"ok after send";
    this->close();
}
void Dialog::cancel(){

    delete this->win->listenSocket;
    this->close();
}
//const QChar* Dialog::ip_search(){
//    win->initServer();
//    return win->listenSocket->serverAddress().toString().constData();
//}

Dialog::~Dialog()
{
    delete ui;
}
