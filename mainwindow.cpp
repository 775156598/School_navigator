#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<string.h>
#include<qdebug.h>
#include<qfile.h>
#include<qbytearray.h>
#include<qfiledialog.h>
#include<qstring.h>
#include<qtextcodec.h>
#include <iostream>
#include<qmovie.h>
#include<fstream>
#include <cstdio>
#include <string>
#include<qimage.h>
#define Num 18
#define Maxedge 5000
using namespace std;

//以下为欧拉回路的头文件配置
#include <cmath>
#include <string>
#include <cstring>
#define mem(a,b) memset(a,b,sizeof(a))
#define M 202
typedef struct         //定义结构型
{
    char name[30] ;
    int number;
}vertex;
vertex ver[Num];
int edge[Num][Num];
int shortest[Num][Num];
int path[Num][Num];

//以下为欧拉回路的配置
typedef long long ll;
struct stack
{
    int top,node[M];
}s;
int e[M][M],n;
int *addre1,*addre2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setMinimumSize(800,500);
    luxian_detail=new ShortDistDialog();
    image_dialog=new ImageDialog();
    bool a=connect(this, SIGNAL(sendData(int,int,QString*)), luxian_detail, SLOT(receiveData(int,int,QString*)));
    qDebug()<<"查询两点间距离链接结果:"<<a;
    bool b=connect(this, SIGNAL(sendData2(QString)), image_dialog, SLOT(receiveData2(QString)));
    qDebug()<<"按钮显示图片功能链接结果:"<<b;

    //此处设置两个不显示的容器，当做中介，用作写入读出。
    ui->result_text->setVisible(false);
    ui->dist_text->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    init();//初始化参数
    QString* str;
    int i=0,j=0;
    while(1)
    {
        i=ui->comboBox->currentIndex()+1;  //由于ver数组从第1项开始存储，因此要加一
        qDebug()<<"初始地点:"<<i;
        j=ui->comboBox_2->currentIndex()+1;
        qDebug()<<"结束地点:"<<j;
        qDebug()<<i<<j;
        if(i<=Num&&i>0&&j<=Num&&j>0)
        {
            floyd();
            str=show4(i,j);
            emit sendData(i,j,str);        //获取lineEdit的输入并且传递出去
            qDebug()<<"传值成功！";
            luxian_detail->show();         //让路线窗口显示
            return;
        }
    }
}

void MainWindow::floyd()
{
    int i=1,j=1,k=1,l=1;
    for(i=1;i<=Num;i++)
    {
        for(j=1;j<=Num;j++)
        {
            shortest[i][j]=edge[i][j];
            path[i][j]=0;
        }
    }
    for(k=1;k<=Num;k++)
    {
        for(i=1;i<=Num;i++)
        {
            for(j=1;j<=Num;j++)
            {
                if(shortest[i][j]>(shortest[i][k]+shortest[k][j]))
                {
                    shortest[i][j]=(shortest[i][k]+shortest[k][j]);
                    path[i][j]=path[j][i]=k;
                }
            }
        }
    }
}

QString* MainWindow::show4(int i,int j)       //显示最短路径及长度。
{
    int k=0,a=i,b=j;
    if(shortest[i][j]!=Maxedge)               //即从这个点可以通往另外一个点
    {
        ui->result_text->setText(tr("从 %1 到 %2 的最短路径为:").arg(ver[i].name).arg(ver[j].name));
        ui->result_text->append(tr("%1").arg(ver[i].name));
        while(path[i][j]!=0)
        {
            k=path[i][j];
            while(path[i][k]!=0)
            {
                k=path[i][k];
            }
            ui->result_text->append(tr("->%1").arg(ver[k].name));
            i=k;
        }
        ui->result_text->append(tr("->%2").arg(ver[j].name));
        QString resultText=ui->result_text->toPlainText();
        QString distText=QString::number(shortest[a][b]);  //int转换成qstring再转换成int
        QString *str=new QString[2];
        str[0]=resultText;
        str[1]=distText;
        return str;
    }
    else
        ui->result_text->setText(tr("从 '%1' 不能到达 '%2' 。").arg(ver[i].name).arg(ver[j].name));
}

void MainWindow::init()                      //初始化地点和长度
{
    QString displayString;
    QString fileName;
    fileName=tr("file_read.txt");
    QFile file(fileName);
    if(file.exists())
        qDebug()<<"yes!!!";
    else qDebug()<<"No!!!";
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    QByteArray line0 = file.readLine();
    int n,m,i=0,j=0,k=0,l=0,x1,x2,len=0;  //此处的len表示两地的长度
    QString str0(line0);
    n=(str0.at(0).toLatin1()-48)*10+(str0.at(1).toLatin1()-48);  //其中n表示节点个数，即景点个数。
    m=(str0.at(3).toLatin1()-48)*10+(str0.at(4).toLatin1()-48);  //m表示边个数，即通往各个景点的路数。
    //qDebug()<<n<<m;
    addre1=new int[m];
    addre2=new int[m];
    int a[m];
    int b[m];
    for(k=1;k<=Num;k++)                  //初始化每天路径为最大值
    {
        for(l=1;l<=Num;l++)
        {
            edge[k][l]=Maxedge;
        }
    }
    //自身到达自身为0
    for(k=1;k<=Num;k++)
    {
        edge[k][k]=0;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        qDebug()<< str;
        int flag=0;
        x1=0;x2=0;len=0;
        while((str.at(flag).toLatin1()-48)>=0&&(str.at(flag).toLatin1()-48)<=9)//在第一个空格时结束
        {
            x1=x1*10+(str.at(flag).toLatin1()-48);
            if(x1==0)
            {
                flag=-1;
                break;
            }
            flag++;
        }
        if(flag==-1) break;
        flag++;
        while((str.at(flag).toLatin1()-48)>=0&&(str.at(flag).toLatin1()-48)<=9)//第二个空格时结束
        {
            x2=x2*10+(str.at(flag).toLatin1()-48);
            flag++;
        }
        flag++;
        while((str.at(flag).toLatin1()-48)>=0&&(str.at(flag).toLatin1()-48)<=9)//行末回车时结束
        {
            len=len*10+(str.at(flag).toLatin1()-48);
            flag++;
        }
        addre1[i]=x1;
        a[i++]=x1;
        addre2[j]=x2;
        b[j++]=x2;
        edge[x1][x2]=edge[x2][x1]=len;   //为顶点间路径赋值
        displayString.append(str);
    }
    for(int q=0;q<m;q++)
    {
        qDebug()<<a[q]<<b[q]<<"\n";
    }
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QString displayString2;
    QFile file2("file_read3.txt");
    if(file2.exists())
        qDebug()<<"yes!!!";
    else qDebug()<<"No!!!";
    if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    int x3=0;
    while(!file2.atEnd())
    {
        QByteArray line = file2.readLine();
        QString str=codec->toUnicode(line);
        qDebug()<<str;
        int flag=0;
        x3=0;
        while((str.at(flag).toLatin1()-48)>=0&&(str.at(flag).toLatin1()-48)<=9)  //在第一个空格时结束
        {
            //qDebug()<<(str.at(flag).toLatin1()-48);
            x3=x3*10+(str.at(flag).toLatin1()-48);
            if(x3==0)
            {
                flag=-1;
                break;
            }
            flag++;
        }
        if(flag==-1) break;
        flag++;
        QString point="";
        while((str.at(flag).toLatin1()-48)!=-38)
        {
            qDebug()<<(str.at(flag));
            point+=(str.at(flag));
            flag++;
        }
        ver[x3].number =x3;
        QByteArray ba = point.toLatin1();
        char *ch;
        ch=ba.data();
        strcpy(ver[x3].name,ch);
    }

    for(int i=0;i<10;i++)
    {
        qDebug()<<"ver["<<i<<"]"<<ver[i].name<<endl;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    init();

    int i,j,u,v,m,degree,num=0,start=0;
    n=18;m=24;   //初始化图的数据
    mem(e,0);
    for(i=0;i<m;i++)
    {
        u=addre1[i];v=addre2[i];
        e[u-1][v-1]=e[v-1][u-1]=1;
    }
    for(i=0;i<n;i++)
    {
        degree=0;
        for(j=0;j<n;j++)
            degree+=e[i][j];
        if(degree&1)
        {
            start=i;
            num++;
        }
    }
    start=ui->comboBox_3->currentIndex();
    if(num==0||num==2) fleury(start);
    else
        qDebug()<<tr("No Euler path\n");

    //一下为判断起点
    if(start==0)
    {
        QMovie* movie = new QMovie("all_routine_playground.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->setSpeed(1000);
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==1)
    {
        QMovie* movie = new QMovie("all_routine_stadium.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==2)
    {
        QMovie* movie = new QMovie("all_routine_court.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==3)
    {
        QMovie* movie = new QMovie("all_routine_TeachingBuilding.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==4)
    {
        QMovie* movie = new QMovie("all_routine_Library.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==5)
    {
        QMovie* movie = new QMovie("all_routine_InfoCenter.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==6)
    {
        QMovie* movie = new QMovie("all_routine_ComplexBuilding.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==7)
    {
        QMovie* movie = new QMovie("all_routine_ExecuteBuilding.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==8)
    {
        QMovie* movie = new QMovie("all_routine_DormDEFH.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==9)
    {
        QMovie* movie = new QMovie("all_routine_DormC.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==10)
    {
        QMovie* movie = new QMovie("all_routine_CommerceStreet.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==11)
    {
        QMovie* movie = new QMovie("all_routine_Canteen.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==12)
    {
        QMovie* movie = new QMovie("all_routine_Canteen.gif");//饭堂跟AB宿舍是同一个
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==13)
    {
        QMovie* movie = new QMovie("all_routine_DormG.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==14)
    {
        QMovie* movie = new QMovie("all_routine_TeacherDepartment.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==15)
    {
        QMovie* movie = new QMovie("all_routine_RestHouse.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==16)
    {
        QMovie* movie = new QMovie("all_routine_ParkingLot.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
    else if(start==17)
    {
        QMovie* movie = new QMovie("all_routine_StudentCenter.gif");
        movie->setScaledSize(ui->campus_picture->size());
        movie->start();
        ui->campus_picture->setMovie(movie);
    }
}

void MainWindow::dfs(int x)
{
    int i;
    s.node[++s.top]=x;
    for(i=0;i<n;i++)
    {
        if(e[i][x]>0)
        {
            e[i][x]=e[x][i]=0;             //删除这条边
            dfs(i);
            break;
        }
    }
}

void MainWindow::fleury(int x)             //这里的x是走完全校的起点
{
    qDebug()<<"start="<<x;
    QString result2="";
    int i,flag;
    s.top=0; s.node[s.top]=x;
    while(s.top>=0)
    {
        flag=0;
        for(i=0;i<n;i++)
        {
            if(e[s.node[s.top]][i]>0)
            {
                flag=1;
                break;
            }
        }
        if(!flag)
        {
            result2.append(tr("-%1").arg(ver[s.node[s.top]+1].name));
            qDebug()<<tr("%1").arg(s.node[s.top--]+1);
        }
        else dfs(s.node[s.top--]);
    }
    result2.append('/');
    qDebug()<<result2;

    //将result2转化成字符数组，方便后面替换qstring中的特定英文单词做准备
    char* ptr;
    QString new_ptr="";
    QByteArray ba;
    ba = result2.toLatin1();
    ptr = ba.data();
    qDebug()<<ptr;
    char* temp=new char[40];
    for(int i=0;i<40;i++)
    {
        temp[i]='\0';
    }
    char ch1,ch;
    int flagg=0;     //判断是否为单词
    int index=0;     //对应于ptr数组
    int index2=0;    //对应于temp
    int if_first=1;  //判断是否为第一个单词，是则不需要在前面加上->
    while(true)
    {
        ch=ptr[index];
        if(ch=='/') break;
        if(ch!='"'&&ch!='\n'&&ch!='-'&&ch!='>')
        {
            flagg=1;     //此时说明是单词
            while(flagg==1)
            {
                ch1=ptr[index];
                if(ch1!='"'&&ch1!='\n'&&ch1!='-'&&ch1!='>'&&ch1!='/')
                {
                    temp[index2]=ch1;
                    index++;
                    index2++;
                    continue;
                }
                else
                {
                    QString s=temp;
                    //qDebug()<<"s的值为"<<s<<"temp的值为"<<temp;
                    QString playground="playground",court="court",TeachingBuliding="TeachingBuliding",library="library",InfoCenter="InfoCenter",ComplexBuliding="ComplexBuliding",ExecutiveBuliding="ExecutiveBuliding",StuDormDEFH="StuDormDEFH";
                    QString stadium="stadium",StuDormC="StuDormC",CommerceStreet="CommerceStreet",Canteen="Canteen",StuDormAB="StuDormAB",StuDormG="StuDormG",TeacherDepartment="TeacherDepartment",RestHouse="RestHouse",ParkingLot="ParkingLot",StuActivityCenter="StuActivityCenter";

                    //以下为将英文单词转化成中文
                    if(s.contains(playground,Qt::CaseSensitive))
                    {
                        qDebug()<<"找到了；";
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
                    temp=new char[40];
                    for(int i=0;i<40;i++)
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
    ui->result_text_2->setText(new_ptr);
    puts("");
}

//下面全部为点击按钮出发图片显示的功能
void MainWindow::on_Playground_clicked()
{
    qDebug()<<"按下了playground";
    QString q="Playground";
    emit sendData2(q);
}
void MainWindow::on_Stadium_clicked()
{
    qDebug()<<"按下了Stadium";
    QString q="Stadium";
    emit sendData2(q);
}
void MainWindow::on_TeachingBuilding_clicked()
{
    qDebug()<<"按下了TeachingBuilding";
    QString q="TeachingBuilding";
    emit sendData2(q);
}
void MainWindow::on_Library_clicked()
{
    qDebug()<<"按下了Library";
    QString q="Library";
    emit sendData2(q);
}
void MainWindow::on_ComplexSchool_clicked()
{
    qDebug()<<"按下了ComplexSchool";
    QString q="ComplexSchool";
    emit sendData2(q);
}
void MainWindow::on_ExecuteBuilding_clicked()
{
    qDebug()<<"按下了ExecuteBuilding";
    QString q="ExecuteBuilding";
    emit sendData2(q);
}
void MainWindow::on_InfoCenter_clicked()
{
    qDebug()<<"按下了InfoCenter";
    QString q="InfoCenter";
    emit sendData2(q);
}
void MainWindow::on_Court_clicked()
{
    qDebug()<<"按下了Court";
    QString q="Court";
    emit sendData2(q);
}
void MainWindow::on_CommerceStreet_clicked()
{
    qDebug()<<"按下了CommerceStreet";
    QString q="CommerceStreet";
    emit sendData2(q);
}
void MainWindow::on_Canteen_clicked()
{
    qDebug()<<"按下了Canteen";
    QString q="Canteen";
    emit sendData2(q);
}
void MainWindow::on_ParkingLot_clicked()
{
    qDebug()<<"按下了ParkingLot";
    QString q="ParkingLot";
    emit sendData2(q);
}
void MainWindow::on_StudentCenter_clicked()
{
    qDebug()<<"按下了StudentCenter";
    QString q="StudentCenter";
    emit sendData2(q);
}
void MainWindow::on_StudentDormAB_clicked()
{
    qDebug()<<"按下了StudentDormAB";
    QString q="StudentDormAB";
    emit sendData2(q);
}
void MainWindow::on_StudentDormC_clicked()
{
    qDebug()<<"按下了StudentDormC";
    QString q="StudentDormC";
    emit sendData2(q);
}
void MainWindow::on_StudentDormDEFH_clicked()
{
    qDebug()<<"按下了StudentDormDEFH";
    QString q="StudentDormDEFH";
    emit sendData2(q);
}
void MainWindow::on_StudentDormG_clicked()
{
    qDebug()<<"按下了StudentDormG";
    QString q="StudentDormG";
    emit sendData2(q);
}
void MainWindow::on_RestHouse_clicked()
{
    qDebug()<<"按下了RestHouse";
    QString q="RestHouse";
    emit sendData2(q);
}
void MainWindow::on_TeacherDepartment_clicked()
{
    qDebug()<<"按下了TeacherDepartment";
    QString q="TeacherDepartment";
    emit sendData2(q);
}
