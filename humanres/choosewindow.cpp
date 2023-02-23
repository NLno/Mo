#include "choosewindow.h"

int ChooseWindow::m_x = 0;
int ChooseWindow::m_y = 0;
bool level_complete[4] = {0, 0, 0, 0};

ChooseWindow::ChooseWindow(QWidget *parent) : QMainWindow(parent)
{

    this->setWindowTitle("Level Choice");
    this->setFixedSize(1920, 1080);

    MyPushButton *backBtn = new MyPushButton(":/new/res/BackButton.png",":/new/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->resize(64, 64);
    backBtn->move(this->width()-backBtn->width()-64,this->height()-backBtn->height()-54);
    backBtn->show();
    connect(backBtn,&MyPushButton::clicked,[=](){
        emit this->chooseBack();
    });

    chooseNumber();
}

void ChooseWindow::chooseNumber()
{
    play = NULL;
    theNewPage();
    sign = true;
}

void ChooseWindow::theNewPage()
{
    //记录关卡
    int k = 1;
    QFile file("./level_record.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int level_tmp=0;
        while (!file.atEnd() && level_tmp < 4)
        {
            QByteArray line = file.readLine();
            QString str(line);
            if(str.isEmpty() == 0)
            {
                if(str.toInt() == 1)
                {
                    level_complete[level_tmp] = true;
                }
                else
                {
                    level_complete[level_tmp] = false;
                }
                level_tmp++;
            }
        }
        file.close();
    }

    //建立关卡
    int i=0;
        for(int j = 0; j < 4; j++,k++)
        {
            //清空按钮和标签
            if(sign == true)
            {
                if(arrayBtn[i][j] != NULL)
                {
                    arrayBtn[i][j]->deleteLater();
                    arrayBtn[i][j] = NULL;
                }

                if(arrayLab[i][j] != NULL)
                {
                    arrayLab[i][j]->deleteLater();
                    arrayLab[i][j] = NULL;
                }
            }

            MyPushButton *num = new MyPushButton(":/new/res/LevelIcon.png");
            num->setFixedSize(201, 201);
            num->move(1080 + j * 181, 760 - j * 210);
            num->setParent(this);
            num->show();
            level_pic.push_back(num);

            QLabel * label = new QLabel;
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::white);
            label->setPalette(pe);
            label->setText(QString::number(k));
            QFont font("Cambria", 64, 75);
            label->setFont(font);
            label->setParent(this);
            label->setFixedSize(200, 200);
            label->move(1080 + j * 181, 760 - j * 210);
            label->show();
            //居中
            label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            //设置标签穿透
            label->setAttribute(Qt::WA_TransparentForMouseEvents);

            //关卡未解锁
            if(j != 0 && level_complete[j-1] == 0)
            {
                num->setEnabled(false);
            }

            arrayBtn[i][j] = num;
            arrayLab[i][j] = label;

            connect(num,&MyPushButton::clicked,[=](){
                //qDebug()<<"Choice the" << k << "level";

                //记录当前窗口坐标
                ChooseWindow::m_x = this->x();
                ChooseWindow::m_y = this->y();
                //创建游戏窗口
                this->play = new playwindow(k);
                this->play->show();
                this->hide();
                //接收back发送的信号
                connect(this->play,&playwindow::chooseBack,[=](){
                    this->move(this->play->x(),this->play->y());
                    this->show();
                    for(int j=1; j<4; j++)
                    {
                        if(level_complete[j-1] == 1)
                        {
                            level_pic[j]->setEnabled(true);
                        }
                    }
                    if(this->play != NULL)
                    {
                        this->play->deleteLater();
                        this->play = NULL;
                    }
                });
            });
        }

}

void ChooseWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/res/start.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
