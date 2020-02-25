#include "imagedialog.h"
#include "ui_imagedialog.h"
#include<qstring.h>
#include<qimage.h>
#include<qpixmap.h>
#include<qdebug.h>
ImageDialog::ImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    //setMinimumSize(1000,700);
}

ImageDialog::~ImageDialog()
{
    delete ui;
}
void ImageDialog::receiveData2(QString point)
{
    this->show();
    ui->Picture->setScaledContents(true);      //让里面的组件自适应背景画布
    QImage *image;
    if(point=="Playground")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("Playground.jpg");
    }
    else if(point=="Stadium")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("Stadium.jpg");
    }
    else if(point=="Library")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("Library.jpg");
    }
    else if(point=="TeachingBuilding")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("TeachingBuilding.jpg");
    }
    else if(point=="Court")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("Court.jpg");
    }
    else if(point=="InfoCenter")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("InfoCenter.jpg");
    }
    else if(point=="ComplexSchool")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("ComplexSchool.jpg");
    }
    else if(point=="ExecuteBuilding")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("ExecuteBuilding.jpg");
    }
    else if(point=="ParkingLot")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("ParkingLot.jpg");
    }
    else if(point=="StudentCenter")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("StudentCenter.jpg");
    }
    else if(point=="Canteen")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("Canteen.jpg");
    }
    else if(point=="CommerceStreet")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("CommerceStreet.jpg");
    }
    else if(point=="StudentDormAB")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("StudentDormAB.jpg");
    }
    else if(point=="TeacherDepartment")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("StudentDormG.jpg");
    }
    else if(point=="StudentDormC")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("StudentDormC.jpg");
    }
    else if(point=="StudentDormG")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("StudentDormG.jpg");
    }
    else if(point=="StudentDormDEFH")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("StudentDormDEFH.jpg");
    }
    else if(point=="RestHouse")
    {
        qDebug()<<"信号发送成功！";
         image=new QImage("RestHouse.jpg");
    }

    QImage* imgScaled = new QImage;
    *imgScaled=image->scaled(ui->Picture->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->Picture->setPixmap(QPixmap::fromImage(*imgScaled));

}
