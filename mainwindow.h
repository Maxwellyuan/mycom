#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "win_qextserialport.h" //加入头文件
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void setComboBoxEnabled(bool status);//添加protected,声明组合框控制函数

private:
    Ui::MainWindow *ui;
    AboutDialog aboutdlg;
    Win_QextSerialPort *myCom; //声明对象

private slots:
    void readMyCom(); //声明读串口槽函数
    void on_sendMsgBtn_clicked();
    void on_clearUpBtn_clicked();
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionClearBytes_triggered();
    void on_actionExit_triggered();
    void on_actionCleanPort_triggered();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
