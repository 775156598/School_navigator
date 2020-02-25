#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<shortdistdialog.h>
#include<imagedialog.h>
#include <QMainWindow>
#include<qlabel.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void floyd();
    QString* show4(int i,int j);
    void init();
    void dfs(int x);
    void fleury(int x);
    ShortDistDialog* luxian_detail;
    ImageDialog* image_dialog;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    //以下为点击按钮出发图片显示的槽函数
    void on_Playground_clicked();
    void on_Stadium_clicked();
    void on_TeachingBuilding_clicked();
    void on_Library_clicked();
    void on_ComplexSchool_clicked();
    void on_ExecuteBuilding_clicked();
    void on_InfoCenter_clicked();
    void on_Court_clicked();
    void on_CommerceStreet_clicked();
    void on_Canteen_clicked();
    void on_ParkingLot_clicked();
    void on_StudentCenter_clicked();
    void on_StudentDormAB_clicked();
    void on_StudentDormC_clicked();
    void on_StudentDormDEFH_clicked();
    void on_StudentDormG_clicked();
    void on_RestHouse_clicked();
    void on_TeacherDepartment_clicked();

signals:                               //定义信号
    void sendData(int,int,QString*);   //用来传递数据的信号
    void sendData2(QString);           //点击按钮传送，用来显示每个地点的实景图片
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
