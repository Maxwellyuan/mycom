#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myCom = NULL;

    //界面控制(按钮和动作)
    ui->sendMsgBtn->setEnabled(false); //开始“发送数据”按钮不可用

    ui->actionClose->setEnabled(false);//设置动作
    //开始“关闭串口”按钮不可用
    ui->actionCleanPort->setEnabled(false);

    ui->statusBar->showMessage(tr("欢迎使用物联网监控系统!"));
}

//析构函数
MainWindow::~MainWindow()
{
    if(myCom != NULL){
        if(myCom->isOpen()){
            myCom->close();
        }
        delete myCom;
    }
    delete ui;
}

//设置各个组合框的函数
void MainWindow::setComboBoxEnabled(bool status)
{
    ui->portNameComboBox->setEnabled(status);
    ui->baudRateComboBox->setEnabled(status);
    ui->dataBitsComboBox->setEnabled(status);
    ui->parityComboBox->setEnabled(status);
    ui->stopBitsComboBox->setEnabled(status);
}

//在下面添加readMyCom()函数的定义，添加如下代码。
void MainWindow::readMyCom() //读串口函数
{
    if(myCom->bytesAvailable()>=38)
    {
        QByteArray temp=myCom->readAll();
        //读取串口缓冲区的所有数据给临时变量temp
        QString buf;

        if(!temp.isEmpty())
        {
            ui->textBrowser->setTextColor(Qt::black);
            if(ui->ccradioButton->isChecked())
            {
                buf = temp;
            }
            else if(ui->chradioButton->isChecked())
            {
                QString str;
                for(int i = 0; i < temp.count(); i++)
                {
                    QString s;
                    s.sprintf("0x%02x, ", (unsigned char)temp.at(i));
                    buf += s;
                }
            }


            ui->textBrowser->setText(ui->textBrowser->document()->toPlainText() + buf);

            QTextCursor cursor = ui->textBrowser->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->textBrowser->setTextCursor(cursor);

            ui->recvbyteslcdNumber->display(ui->recvbyteslcdNumber->value() + temp.size());
            ui->statusBar->showMessage(tr("成功读取%1字节数据").arg(temp.size()));

            //ui->textBrowser->insertPlainText(temp);
            //将串口的数据显示在窗口的文本浏览器中

            qDebug()<<"temp长度:"<<temp.size()<<"!";
            qDebug()<<"缓冲区:"<<myCom->bytesAvailable()<<"bytes";
            qDebug()<<"第一个temp值:"<<temp[0]<<"!";

            //qDebug()<<"read:"<<myCom->bytesAvailable()<<"bytes";

            ui->textBrowser_2->insertPlainText(temp.mid(7,2)); //将串口的数据显示在窗口2的文本浏览器中
            QTextCursor cursor_2 = ui->textBrowser_2->textCursor();
            cursor_2.movePosition(QTextCursor::End);
            ui->textBrowser_2->setTextCursor(cursor_2);

            ui->textBrowser_3->insertPlainText(temp.mid(11,2)); //将串口的数据显示在窗口3的文本浏览器中
            QTextCursor cursor_3 = ui->textBrowser_3->textCursor();
            cursor_3.movePosition(QTextCursor::End);
            ui->textBrowser_3->setTextCursor(cursor_3);

            ui->textBrowser_4->insertPlainText(temp.mid(15,2));//将串口的数据显示在窗口4的文本浏览器中
            QTextCursor cursor_4 = ui->textBrowser_4->textCursor();
            cursor_4.movePosition(QTextCursor::End);
            ui->textBrowser_4->setTextCursor(cursor_4);

            ui->textBrowser_5->insertPlainText(temp.mid(19,2));//将串口的数据显示在窗口5的文本浏览器中
            QTextCursor cursor_5 = ui->textBrowser_5->textCursor();
            cursor_5.movePosition(QTextCursor::End);
            ui->textBrowser_5->setTextCursor(cursor_5);

            ui->textBrowser_6->insertPlainText(temp.mid(23,2));//将串口的数据显示在窗口6的文本浏览器中
            QTextCursor cursor_6 = ui->textBrowser_6->textCursor();
            cursor_6.movePosition(QTextCursor::End);
            ui->textBrowser_6->setTextCursor(cursor_6);

            ui->textBrowser_7->insertPlainText(temp.mid(27,2));//将串口的数据显示在窗口7的文本浏览器中
            QTextCursor cursor_7 = ui->textBrowser_7->textCursor();
            cursor_7.movePosition(QTextCursor::End);
            ui->textBrowser_7->setTextCursor(cursor_7);

            ui->textBrowser_8->insertPlainText(temp.mid(31,2));//将串口的数据显示在窗口8的文本浏览器中
            QTextCursor cursor_8 = ui->textBrowser_8->textCursor();
            cursor_8.movePosition(QTextCursor::End);
            ui->textBrowser_8->setTextCursor(cursor_8);

            ui->textBrowser_9->insertPlainText(temp.mid(35,2));//将串口的数据显示在窗口7的文本浏览器中
            QTextCursor cursor_9 = ui->textBrowser_9->textCursor();
            cursor_9.movePosition(QTextCursor::End);
            ui->textBrowser_9->setTextCursor(cursor_9);
        }
    }
}

//打开串口的动作
void MainWindow::on_actionOpen_triggered()
{
    QString portName = ui->portNameComboBox->currentText(); //获取串口名
    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
    //定义串口对象，并传递参数，在构造函数里对其进行初始化
    //myCom ->open(QIODevice::ReadWrite); //打开串口

    //通过弹出的对话判断是否打开串口
    if(myCom->open(QIODevice::ReadWrite))
    {
        //打开串口后再对串口进行配置
        if(ui->baudRateComboBox->currentText()==tr("9600")) //根据组合框内容对串口进行设置
            myCom->setBaudRate(BAUD9600);
        else if(ui->baudRateComboBox->currentText()==tr("115200"))
            myCom->setBaudRate(BAUD115200); //设置波特率

        if(ui->dataBitsComboBox->currentText()==tr("8"))
            myCom->setDataBits(DATA_8);
        else if(ui->dataBitsComboBox->currentText()==tr("7"))
            myCom->setDataBits(DATA_7); //设置数据位

        if(ui->parityComboBox->currentText()==tr("无"))
            myCom->setParity(PAR_NONE);
        else if(ui->parityComboBox->currentText()==tr("奇"))
            myCom->setParity(PAR_ODD);
        else if(ui->parityComboBox->currentText()==tr("偶"))
            myCom->setParity(PAR_EVEN); //设置奇偶校验

        if(ui->stopBitsComboBox->currentText()==tr("1"))
            myCom->setStopBits(STOP_1);
        else if(ui->stopBitsComboBox->currentText()==tr("2"))
            myCom->setStopBits(STOP_2); //设置停止位

        myCom->setFlowControl(FLOW_OFF); //设置数据流控制，我们使用无数据流控制的默认设置
        myCom->setTimeout(10); //设置延时
        connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
        //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作

        QMessageBox::information(this, tr("打开成功"), tr("已成功打开串口") + portName, QMessageBox::Ok);

        //界面控制
        ui->sendMsgBtn->setEnabled(true); //打开串口后“发送数据”按钮可用

        setComboBoxEnabled(false);//设置各个组合框不可用

        ui->actionOpen->setEnabled(false);//设置动作
        ui->actionClose->setEnabled(true);
        ui->actionCleanPort->setEnabled(true);

    }
    else
    {
        QMessageBox::critical(this, tr("打开失败"), tr("未能打开串口 ") + portName + tr("\n该串口设备不存在或已被占用"), QMessageBox::Ok);
        return;
    }

    ui->statusBar->showMessage(tr("打开串口成功"));
}

//关闭串口的动作
void MainWindow::on_actionClose_triggered()
{
    myCom->close(); //关闭串口，该函数在win_qextserialport.cpp文件中定义

    //界面控制
    ui->sendMsgBtn->setEnabled(false); //关闭串口后“发送数据”按钮不可用

    setComboBoxEnabled(true); //设置各个组合框可用

    ui->actionOpen->setEnabled(true);//设置动作
    //关闭串口后“打开串口”动作可用
    ui->actionClose->setEnabled(false);//关闭串口后“关闭串口”动作不可用
    ui->actionCleanPort->setEnabled(false);
}


void MainWindow::on_sendMsgBtn_clicked() //发送数据槽函数
{
    myCom->write(ui->sendMsgLineEdit->text().toLatin1());
    //以Latin1码形式将行编辑框中的数据写入串口,注意修改为toLatin1()，Latin1,向下兼容ASCII码。
}

//清空记录
void MainWindow::on_clearUpBtn_clicked()
{
    ui->textBrowser->clear();
    ui->statusBar->showMessage(tr("记录已经清空"));//statusBar似乎不添加也存在
}

//计数器清零
void MainWindow::on_actionClearBytes_triggered()
{
    if(ui->recvbyteslcdNumber->value() == 0){
        QMessageBox::information(this, tr("提示消息"), tr("貌似已经清零了呀:)"), QMessageBox::Ok);
    }else{
        ui->recvbyteslcdNumber->display(0);
        ui->statusBar->showMessage(tr("计数器已经清零"));
    }
}

//退出程序
void MainWindow::on_actionExit_triggered()
{
    this->close();
}

//清空串口中的I/O数据
void MainWindow::on_actionCleanPort_triggered()
{
    myCom->flush();
}

//关于
void MainWindow::on_actionAbout_triggered()
{
    aboutdlg.show();
    // 在主窗口中间显示
    int x =this->x() + (this->width() - aboutdlg.width()) / 2;
    int y =this->y() + (this->height() - aboutdlg.height()) / 2;
    aboutdlg.move(x, y);
    ui->statusBar->showMessage(tr("关于物联网监控系统"));
}
