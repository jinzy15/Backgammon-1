#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;
namespace Ui {
class connectDialog;
}

class connectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit connectDialog(MainWindow* ,QWidget *parent = 0);
    ~connectDialog();
      QString string;
      //const QString& str;
      MainWindow* client;
public slots:
    void displayed(const QString&);
    void del();
    void ok();
private:
    Ui::connectDialog *ui;
};

#endif // CONNECTDIALOG_H
