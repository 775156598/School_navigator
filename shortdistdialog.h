#ifndef SHORTDISTDIALOG_H
#define SHORTDISTDIALOG_H

#include <QDialog>
//#include<mainwindow.h>
namespace Ui {
class ShortDistDialog;
}

class ShortDistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShortDistDialog(QWidget *parent = 0);
    ~ShortDistDialog();

private slots:
    void receiveData(int,int,QString*);   //接收传递过来的数据的槽

private:
    Ui::ShortDistDialog *ui;
};

#endif // SHORTDISTDIALOG_H
