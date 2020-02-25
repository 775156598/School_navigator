#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(QWidget *parent = 0);
    ~ImageDialog();
private slots:
    void receiveData2(QString);   //接收传递过来的数据的槽
private:
    Ui::ImageDialog *ui;
};

#endif // IMAGEDIALOG_H
