//GitHub测试
#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec> //加入头文件

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
