#include "shortdistdialog.h"
#include "ui_shortdistdialog.h"
#include<qbytearray.h>
#include<qmovie.h>
#include<qdebug.h>
#include<qstring.h>
ShortDistDialog::ShortDistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShortDistDialog)
{
    ui->setupUi(this);
    //setMinimumSize(1200,800);
}

ShortDistDialog::~ShortDistDialog()
{
    delete ui;
}
void ShortDistDialog::receiveData(int start,int end,QString* result)
{
    qDebug()<<start;
    qDebug()<<start<<end<<result[0]<<result[1].toInt();
    result[0].append('/');
    qDebug()<<"result[1]的值为"<<result[0];
    char* ptr;
    QString new_ptr="";
    QByteArray ba;
    ba = result[0].toLatin1();
    ptr = ba.data();
    qDebug()<<ptr;
    char* temp=new char[60];
    for(int i=0;i<60;i++)
    {
        temp[i]='\0';
    }
    char ch1,ch;
    int flagg=0;
    int index=0;
    int index2=0;
    int if_first=1;
    while(true)
    {
        ch=ptr[index];
        if(ch=='/') break;
        if(ch!='"'&&ch!='\n'&&ch!='-'&&ch!='>')
        {
            flagg=1;
            while(flagg==1)
            {
                ch1=ptr[index];
                if(ch1!='"'&&ch1!='\n'&&ch1!='-'&&ch1!='>'&&ch1!='/')
                {
                    //if(ch1=='/') break;
                    temp[index2]=ch1;
                    index++;
                    index2++;
                    continue;
                }
                else
                {
                    QString s=temp;
                    qDebug()<<"s的值为"<<s;
                    QString playground="playground",court="court",TeachingBuliding="TeachingBuliding",library="library",InfoCenter="InfoCenter",ComplexBuliding="ComplexBuliding",ExecutiveBuliding="ExecutiveBuliding",StuDormDEFH="StuDormDEFH";
                    QString stadium="stadium",StuDormC="StuDormC",CommerceStreet="CommerceStreet",Canteen="Canteen",StuDormAB="StuDormAB",StuDormG="StuDormG",TeacherDepartment="TeacherDepartment",RestHouse="RestHouse",ParkingLot="ParkingLot",StuActivityCenter="StuActivityCenter";
                    if(s==playground)
                    {
                        if_first?new_ptr.append("运动场"):new_ptr.append("\n->运动场");
                        if_first=0;
                        qDebug()<<new_ptr;
                    }
                    else if(s==stadium)
                    {
                        if_first?new_ptr.append("体育馆"):new_ptr.append("\n->体育馆");
                        if_first=0;
                    }
                    else if(s==court)
                    {
                        if_first?new_ptr.append("篮球场"):new_ptr.append("\n->篮球场");
                        if_first=0;
                    }
                    else if(s==TeachingBuliding)
                    {
                        if_first?new_ptr.append("教学楼"):new_ptr.append("\n->教学楼");
                        if_first=0;
                    }
                    else if(s==library)
                    {
                        if_first?new_ptr.append("图书馆"):new_ptr.append("\n->图书馆");
                        if_first=0;
                    }
                    else if(s==InfoCenter)
                    {
                        if_first?new_ptr.append("信息中心"):new_ptr.append("\n->信息中心");
                        if_first=0;
                    }
                    else if(s==ComplexBuliding)
                    {
                        if_first?new_ptr.append("综合楼"):new_ptr.append("\n->综合楼");
                        if_first=0;
                    }
                    else if(s==ExecutiveBuliding)
                    {
                        if_first?new_ptr.append("行政楼"):new_ptr.append("\n->行政楼");
                        if_first=0;
                    }
                    else if(s==StuDormDEFH)
                    {
                        if_first?new_ptr.append("学生宿舍D，E，F，H"):new_ptr.append("\n->学生宿舍D，E，F，H");
                        if_first=0;
                    }
                    else if(s==StuDormC)
                    {
                        if_first?new_ptr.append("学生宿舍C"):new_ptr.append("\n->学生宿舍C");
                        if_first=0;
                    }
                    else if(s==CommerceStreet)
                    {
                        if_first?new_ptr.append("商业街"):new_ptr.append("\n->商业街");
                        if_first=0;
                    }
                    else if(s==Canteen)
                    {
                        if_first?new_ptr.append("饭堂"):new_ptr.append("\n->饭堂");
                        if_first=0;
                    }
                    else if(s==StuDormAB)
                    {
                        if_first?new_ptr.append("学生宿舍A，B"):new_ptr.append("\n->学生宿舍A，B");
                        if_first=0;
                    }
                    else if(s==StuDormG)
                    {
                        if_first?new_ptr.append("学生宿舍G"):new_ptr.append("\n->学生宿舍G");
                        if_first=0;
                    }
                    else if(s==TeacherDepartment)
                    {
                        if_first?new_ptr.append("教师公寓"):new_ptr.append("\n->教师公寓");
                        if_first=0;
                    }
                    else if(s==RestHouse)
                    {
                        if_first?new_ptr.append("招待所"):new_ptr.append("\n->招待所");
                        if_first=0;
                    }
                    else if(s==ParkingLot)
                    {
                        if_first?new_ptr.append("停车场"):new_ptr.append("\n->停车场");
                        if_first=0;
                    }
                    else if(s==StuActivityCenter)
                    {
                        if_first?new_ptr.append("学生活动中心"):new_ptr.append("\n->学生活动中心");
                        if_first=0;
                    }
                    if(ch1=='/') break;
                    temp=new char[60];
                    for(int i=0;i<60;i++)
                    {
                        temp[i]='\0';
                    }
                    index2=0;
                    index++;
                    flagg=0;
                    break;
                }

            }
            if(ch1=='/') break;
        }
        else
        {
            index++;
            continue;
        }
    }
    ui->routine_result->setText(new_ptr);
    ui->dist_result->setText(result[1]);
}


