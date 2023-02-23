#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

namespace Ui {
class MyPushButton;
}

class MyPushButton : public QPushButton
{
    Q_OBJECT

public:

    MyPushButton(QString normalImg,QString pressImg = "");  //normalImg代表正常图片，pressImg按下后显示

    void zoom();                            //点击开始动画
    void mousePressEvent(QMouseEvent *e);   //重写鼠标按下
    void mouseReleaseEvent(QMouseEvent *e); //重写鼠标释放

    QString m_normalImg;
    QString m_pressImg;

private:
    Ui::MyPushButton *ui;

};

#endif // MYPUSHBUTTON_H
