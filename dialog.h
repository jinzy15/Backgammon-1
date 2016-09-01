#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include <QChar>

class MainWindow;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(MainWindow*, QWidget *parent = 0);
    ~Dialog();
//    const QChar* ip_search();
public slots:
    void ok();
    void cancel();

private:
    Ui::Dialog *ui;
    MainWindow* win;
};

#endif // DIALOG_H
