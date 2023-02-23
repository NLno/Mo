#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include "mypushbutton.h"
#include "playwindow.h"
#include <QMainWindow>
#include <QAction>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QMap>
#include <QVector>
#include <QFile>

class ChooseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseWindow(QWidget *parent = nullptr);


    void paintEvent(QPaintEvent *);

    void chooseNumber();
    void theNewPage();

    playwindow *play;
    QLabel *arrayLab[1][5];
    MyPushButton *arrayBtn[1][5];
    QList<MyPushButton*> level_pic;

    static int m_x;//记录窗口位置
    static int m_y;

    bool sign = false;//第一次创建按钮和标签标志

signals:
    void chooseBack();  //back信号，主界面接收

public slots:

};

#endif // CHOOSEWINDOW_H
