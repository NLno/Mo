#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QAction>
#include "mypushbutton.h"
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QPropertyAnimation>
#include <QVector>
#include <QMovie>
#include <QLineEdit>
#include <QImage>
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QTextStream>

class playwindow : public QMainWindow
{
    Q_OBJECT

public:

    playwindow(int playIndex);      //含关卡序号构造函数
    ~playwindow();                  //关卡界面清空后清空相关变量
    void ui();
    void paintEvent(QPaintEvent *);

    void doitBtn();

    void showLevel();//显示第几关
    void createbox();
    void showRect();//显示各种积木
    void showin();
    void showout();
    void showextra();

    void copyData(); //获得关卡数据
    void gameWin();
    void gameLose();
    void gameError(int order);
    void addonecmd(int order, QString str);

    int m_playIndex;//记录目前开始关卡
    QLabel* arrow = new QLabel(this);
    QLineEdit* pNormalLineEdit = new QLineEdit(this);
    QList<QLabel*> in_label;
    QList<QLabel*> out_label;
    QList<QLabel*> ex_label1;//空地序号
    QList<QLabel*> ex_label2;//空地数字大小
    QList<MyPushButton*> in_pic;
    QList<MyPushButton*> out_pic;
    QList<MyPushButton*> ex_pic;
    QLabel* nowbox = new QLabel(this);
    QMovie* robot = new QMovie(":new/res/miku.gif");
    QLabel* robotlabel = new QLabel(this);
    MyPushButton *backBtn = new MyPushButton(":/new/res/BackButton.png",":/new/res/BackButtonSelected.png");

signals:
    void chooseBack();  //back信号，主界面接收

public slots:
    void readonecmd(); //文本输入框回车添加命令
    void readcmdlist();

};

#endif // PLAYWINDOW_H
