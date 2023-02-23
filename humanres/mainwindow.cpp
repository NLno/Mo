#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QtGui>
#include <QImage>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Human Resource");
    this->setFixedSize(1920, 1080);

    MyPushButton *startBtn = new MyPushButton(":new/res/StartButton.png");
    startBtn->resize(512, 512);
    startBtn->move(1240, 300);
    startBtn->setParent(this);

    QMovie* robot = new QMovie(":new/res/mikubig.gif");
    QLabel* robotlabel = new QLabel(this);
    robotlabel->resize(600, 600);
    robotlabel->move(360, 280);
    robotlabel->setMovie(robot);
    robot->start();

    choose = new ChooseWindow;
    //接收次窗口发出的back信号
    connect(choose,&ChooseWindow::chooseBack,[=](){
       QTimer::singleShot(80,this,[=](){
        this->move(this->choose->x(), this->choose->y());
        this->show();
        choose->hide();
        });
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        startBtn->zoom();
        QTimer::singleShot(50,this,[=](){
            this->hide();
            choose->show();
            choose->move(this->x(), this->y());
        });
    });

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/res/start.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

