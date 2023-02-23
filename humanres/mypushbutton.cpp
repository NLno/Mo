#include "mypushbutton.h"
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include <QPropertyAnimation>

//normalImg代表正常图片，pressImg按下后显示
MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->m_pressImg = pressImg;
    this->m_normalImg = normalImg;

    QPainter painter;
    QPixmap pix;
    bool res = pix.load(normalImg);
    if(!res)
    {
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px};");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

}

//点击开始动画
void MyPushButton::zoom()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    QPropertyAnimation *animation1 = new QPropertyAnimation(this,"geometry");

    //向下跳动画
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->m_pressImg != "")
    {
        QPixmap pix;
        pix.load(this->m_normalImg);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->m_pressImg != "")
    {
        QPixmap pix;
        pix.load(this->m_pressImg);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    QPushButton::mouseReleaseEvent(e);

}
