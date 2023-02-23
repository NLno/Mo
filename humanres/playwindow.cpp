#include "playwindow.h"
#include "choosewindow.h"

QVector<int> output_show;
QVector<int> input;
QVector<int> output_goal;
QVector<int> output;
int emptyPlace[3];
int places = 0;
bool whether_emptyPlace[3] = {1, 1, 1};
extern bool level_complete[4];
int present;
bool whether_inbox = 1;
bool whether_present_zero;
int numOforder[4] = {2, 8, 8, 8};

struct cmd
{
    QString name;
    int num;
    int order;
    int (*func)(int);
};

int number_order=0;
cmd cmd[15];
//指令最多输入15条

void Delay_MSec(int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < _Timer )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

playwindow::playwindow(int playIndex)
{
    //窗口移动到记录的坐标位置
    this->move(ChooseWindow::m_x,ChooseWindow::m_y);
    this->m_playIndex = playIndex;

    ui();
    doitBtn();
    showLevel();
    copyData();
    createbox();
    showRect();

    robotlabel->resize(250, 250);
    robotlabel->move(600, 440);
    robotlabel->setMovie(robot);
    robot->start();

    //输入框
    pNormalLineEdit->move(1460,260);
    pNormalLineEdit->setMaximumWidth(360);
    pNormalLineEdit->setFixedWidth(400);
    pNormalLineEdit->setMaximumHeight(60);
    pNormalLineEdit->setFixedHeight(72);
    pNormalLineEdit->setPlaceholderText("press Enter to send");
    //限制最大输入长度
    pNormalLineEdit->setMaxLength(40);
    pNormalLineEdit->setStyleSheet("border-style: outset; border-width: 2px; border-color: rgb(0,0,0); border-radius:10px; padding:2px 4px");
    pNormalLineEdit->setClearButtonEnabled(true);
    pNormalLineEdit->setEchoMode(QLineEdit::Normal);
    connect(pNormalLineEdit, SIGNAL(returnPressed()), this, SLOT(readonecmd()));

    backBtn->setParent(this);
    backBtn->resize(64, 64);
    backBtn->move(this->width()-backBtn->width()-64,this->height()-backBtn->height()-54);
    backBtn->show();
    connect(backBtn,&MyPushButton::clicked,[=](){
        emit this->chooseBack();
    });

    QImage *img = new QImage();
    img->load(":new/res/click.png");
    arrow->setPixmap(QPixmap::fromImage(*img));
    arrow->move(1440, 410);
    arrow->show();

}

void playwindow::ui()
{
    this->setWindowTitle("Gaming...");
    this->setFixedSize(1920, 1080);
}

void playwindow::doitBtn(){
    MyPushButton* doBtn = new MyPushButton(":new/res/do.png", ":/new/res/done.png");
    doBtn->setParent(this);
    doBtn->resize(164, 164);
    doBtn->move(64, 64);
    doBtn->show();
    connect(doBtn,&MyPushButton::clicked,[=](){
        doBtn->setEnabled(false);
        pNormalLineEdit->setEnabled(false);
        readcmdlist();
    });
}

void playwindow::showLevel()
{
    QLabel *lab = new QLabel;
    QString str = QString("level: %1").arg(m_playIndex);
    QFont font;
    font.setFamily("Cambria");
    font.setPointSize(16);
    lab->setFont(font);
    lab->setText(str);
    lab->move(1460, -120);
    lab->setParent(this);
    lab->show();

    QString str1;
    switch(m_playIndex)
    {
    case 1: str1 = "依次平移"; break;
    case 2: str1 = "相邻二者先后取差"; break;
    case 3: str1 = "保留相邻二者相等的数"; break;
    case 4: str1 = "八倍化当前数"; break;
    }
    QLabel* lab1 = new QLabel;
    lab1->setFont(font);
    lab1->setText(str1);
    lab1->move(1460, -60);
    lab1->setParent(this);
    lab1->show();
}

void playwindow::copyData()
{
    QVector<int> in;
    QVector<int> out;
    switch(this->m_playIndex)
    {
    case 1:
    {
        output.reserve(2);
        int input_tmp[2] = {1, 2};
        for(int i=0; i<2; i++)
        {
            in.push_back(input_tmp[i]);
        }
        input.swap(in);
        int output_tmp[2] = {1, 2};
        for(int i=0; i<2; i++)
        {
            out.push_back(output_tmp[i]);
        }
        output_goal.swap(out);
        places = 0;
        break;
    }

    case 2:
    {
        output.reserve(8);
        int input_tmp[8] = {3, 9, 5, 1, -2, -2, 9, -9};
        for(int i=0; i<8; i++)
        {
            in.push_back(input_tmp[i]);
        }
        input.swap(in);
        int output_tmp[8] = {-6, 6, 4, -4, 0, 0, 18, -18};
        for(int i=0; i<8; i++)
        {
            out.push_back(output_tmp[i]);
        }
        output_goal.swap(out);
        places = 3;
        break;
    }

    case 3:
    {
        output.reserve(2);
        int input_tmp[8] = {6, 2, 7, 7, -9, 3, -3, -3};
        for(int i=0; i<8; i++)
        {
            in.push_back(input_tmp[i]);
        }
        input.swap(in);
        int output_tmp[2] = {7, -3};
        for(int i=0; i<2; i++)
        {
            out.push_back(output_tmp[i]);
        }
        output_goal.swap(out);
        places = 3;
        break;
    }

    case 4:
    {
        output.reserve(4);
        int input_tmp[4] = {1, -3, 2, 0};
        for(int i=0; i<4; i++)
        {
            in.push_back(input_tmp[i]);
        }
        input.swap(in);
        int output_tmp[4] = {8, -24, 16, 0};
        for(int i=0; i<4; i++)
        {
            out.push_back(output_tmp[i]);
        }
        output_goal.swap(out);
        places = 3;
        break;
    }
    }
}

bool exist(int num)
{
    if (num < 0 || num > places - 1)
        return true;
    else
        return false;
}

int inbox(int num)
{
    if (input.size() == 0)
        return 100;
    present = input[0];
    input.erase(input.begin());
    whether_inbox = 0;
    return 0;
}

int outbox(int num)
{
    if (whether_inbox)
        return 404;
    output.push_back(present);
    output_show.insert(output_show.begin(), present);
    whether_inbox = 1;
    return 0;
}

int add(int num)
{
    if (whether_inbox || exist(num) || whether_emptyPlace[num])
        return 404;
    present += emptyPlace[num];
    return 0;
}

int sub(int num)
{
    if (whether_inbox || exist(num) || whether_emptyPlace[num])
        return 404;
    present -= emptyPlace[num];
    return 0;
}

int copyto(int num)
{
    if (whether_inbox || exist(num))
        return 404;
    emptyPlace[num] = present;
    whether_emptyPlace[num] = 0;
    return 0;
}

int copyfrom(int num)
{
    if (exist(num) || whether_emptyPlace[num])
        return 404;
    present = emptyPlace[num];
    whether_inbox = 0;
    return 0;
}

int jump(int num)
{
    return num;
}

int jumpifzero(int num)
{
    if (whether_inbox)
        return 404;
    if (present == 0)
    {
        whether_present_zero = 1;
        return num;
    }
    else
    {
        whether_present_zero = 0;
        return num;
    }
}

int (*func[8])(int) = {inbox, outbox, add, sub, copyto, copyfrom, jump, jumpifzero};
QString name[8] = {"inbox", "outbox", "add", "sub", "copyto", "copyfrom", "jump", "jumpifzero"};

void playwindow::createbox()
{
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    QFont font("Cambria", 18, 75);
    nowbox->setPalette(pe);
    nowbox->setFont(font);
    nowbox->setFixedSize(64, 64);
    nowbox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    nowbox->move(685, 440);

    for(int i=0; i<8; i++)
    {
        MyPushButton *num = new MyPushButton(":/new/res/BoxIcon.png");
        num->setFixedSize(64, 64);
        num->setParent(this);
        num->setEnabled(false);
        num->move(240, 560 + 60*i);
        in_pic.push_back(num);
        MyPushButton *num1 = new MyPushButton(":/new/res/BoxIcon.png");
        num1->setFixedSize(64, 64);
        num1->setParent(this);
        num1->setEnabled(false);
        num1->move(1160, 560 + 60*i);
        out_pic.push_back(num1);

        QLabel * label = new QLabel(this);
        label->setPalette(pe);
        label->setFont(font);
        label->setFixedSize(num->width(), num->height());
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->move(240, 560 + 60*i);
        in_label.push_back(label);
        QLabel * label1 = new QLabel(this);
        label1->setPalette(pe);
        label1->setFont(font);
        label1->setFixedSize(num->width(), num->height());
        label1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label1->move(1160, 560 + 60*i);
        out_label.push_back(label1);

        if(i < places)
        {
            MyPushButton *num2 = new MyPushButton(":/new/res/BoxIcon.png");
            num2->setFixedSize(64, 64);
            num2->setParent(this);
            num2->setEnabled(false);
            num2->move(605 + 80*i, 720);
            ex_pic.push_back(num2);

            QLabel * label2 = new QLabel(this);
            label2->setPalette(pe);
            label2->setFont(font);
            label2->setFixedSize(num->width(), num->height());
            label2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            label2->move(605 + 80*i, 760);
            ex_label1.push_back(label2);
            QLabel * label3 = new QLabel(this);
            label3->setPalette(pe);
            label3->setFont(font);
            label3->setFixedSize(num->width(), num->height());
            label3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            label3->move(605 + 80*i, 720);
            ex_label2.push_back(label3);
        }
    }
}

void playwindow::showin()
{
    //qDebug()<< "input now" << input.size() << "boxes";
    for(int i=0; i<8; i++)
    {
        if(i < input.size())
        {
            in_pic[i]->show();
            in_label[i]->setText(QString::number(input[i]));
            in_label[i]->show();
        }
        else
        {
            in_pic[i]->hide();
            in_label[i]->hide();
        }
    }
}

void playwindow::showout()
{
    //qDebug()<< "output now" << output_show.size() << "boxes";
    for(int i=0; i<8; i++)
    {
        if(i < output_show.size())
        {
            out_label[i]->setText(QString::number(output_show[i]));
            out_pic[i]->show();
            out_label[i]->show();
        }
        else
        {
            out_pic[i]->hide();
            out_label[i]->hide();
        }
    }
}

void playwindow::showextra()
{
    if(whether_inbox == 0)
    {
        nowbox->setText(QString::number(present));
        nowbox->show();
    }
    else
    {
        nowbox->hide();
    }

    if(places != 0)
    {
        for(int i=0; i<places; i++)
        {
            ex_pic[i]->show();
            ex_label1[i]->setText(QString::number(i));
            ex_label1[i]->show();
            if(whether_emptyPlace[i] == 0)
            {
                ex_label2[i]->setText(QString::number(emptyPlace[i]));
                ex_label2[i]->show();
            }
            else
            {
                ex_label2[i]->hide();
            }
        }
    }
}

void playwindow::showRect()
{
    showin();
    showout();
    showextra();
    Delay_MSec(500);
}

void playwindow::addonecmd(int order, QString str)
{
    QLabel *label = new QLabel;
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    label->setPalette(pe);
    label->setText(str);
    QFont font("Cambria", 16, 50);
    label->setFont(font);
    label->setParent(this);
    label->move(1500, 180 + 40*order);
    //设置为透明
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setStyleSheet("background:transparent");
    label->show();
}

void playwindow::readonecmd()
{
    QString str = pNormalLineEdit->text();
    if(!str.isEmpty() && number_order < 15)
    {
        if(str == "inbox")
        {
            cmd[number_order].name = str;
            cmd[number_order].order = 0;
            cmd[number_order].num = 0;
            cmd[number_order].func = func[0];
            addonecmd(number_order, str);
            number_order++;
        }
        else if(str == "outbox")
        {
            cmd[number_order].name = str;
            cmd[number_order].order = 1;
            cmd[number_order].num = 0;
            cmd[number_order].func = func[1];
            addonecmd(number_order, str);
            number_order++;
        }
        else
        {
            QStringList list = str.split(" ");
            cmd[number_order].name = list[0];
            int cnt = 0;
            addonecmd(number_order, str);
            for (int j = 2; j < numOforder[m_playIndex - 1]; j++)
            {
                if (cmd[number_order].name == name[j])
                {
                    cmd[number_order].order = j;
                    cmd[number_order].func = func[j];
                    cmd[number_order].num = QString(list[1]).toInt();
                    cnt = 1;
                    number_order++;
                    break;
                }
            }
            if (cnt == 0)
            {
                arrow->move(1440, 410 + 40*number_order);
                gameError(number_order+1);
                //qDebug()<< "Error on instruction " << number_order + 1;
            }
        }
    }
    pNormalLineEdit->clear();//清空输入框
}

void playwindow::readcmdlist()
{
    for (int i = 0; i < number_order; i++)
    {
        //qDebug()<< "Now the " << i + 1 << "step";
        arrow->move(1440, 410 + 40*i);
        int msg = cmd[i].func(cmd[i].num);
        if(cmd[i].order == 0)
        {
            robotlabel->move(240, 440);
            Delay_MSec(200);
            robotlabel->move(600, 440);
        }
        else if(cmd[i].order == 1)
        {
            robotlabel->move(960, 440);
            Delay_MSec(200);
            robotlabel->move(600, 440);
        }
        else
        {
            Delay_MSec(200);
        }
        if (cmd[i].order == 6)
        {
            if (msg < 1 || msg > number_order)
            {
                //qDebug()<< "Error on instruction " << i + 1;
                gameError(i + 1);
                break;
            }
            else
            {
                i = msg - 2;
                showRect();
                continue;
            }
        }
        else if (cmd[i].order == 7)
        {
            if (msg < 1 || msg > number_order)
            {
                //qDebug()<< "Error on instruction " << i + 1;
                gameError(i + 1);
                break;
            }
            else
            {
                if (whether_present_zero)
                {
                    i = msg - 2;
                    showRect();
                }
                else
                    continue;
            }
        }
        if (msg == 404)
        {
            //qDebug()<< "Error on instruction " << i + 1;
            gameError(i + 1);
            break;
        }
        else if (msg == 100)
        {
            break;
        }
        if(cmd[i].order == 1)
        {
            nowbox->move(1045, 440);
        }
        showRect();
        if(cmd[i].order == 1)
        {
            nowbox->move(685, 440);
        }
    }

    if (output == output_goal)
    {
        //qDebug()<< "Success";
        level_complete[m_playIndex - 1] = 1;
        QFile file("./level_record.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            for(int m=0; m<4; m++)
            {
                QTextStream out(&file);
                if(level_complete[m] == true)
                {
                    out<<1<<endl;
                }
                else
                {
                    out<<0<<endl;
                }
            }
            file.close();
        }
        gameWin();
    }
    else
    {
        //qDebug()<< "Fail";
        gameLose();
    }
}

void playwindow::gameWin()
{
    MyPushButton *num = new MyPushButton(":/new/res/win.png");
    num->setParent(this);
    num->setEnabled(false);
    num->setFixedSize(400, 400);
    num->move(480, 360);
    num->show();
    backBtn->setEnabled(false);
    Delay_MSec(3000);
    emit this->chooseBack();
}

void playwindow::gameLose()
{
    MyPushButton *num = new MyPushButton(":/new/res/lose.png");
    num->setParent(this);
    num->setEnabled(false);
    num->setFixedSize(400, 400);
    num->move(480, 360);
    num->show();
    backBtn->setEnabled(false);
    Delay_MSec(3000);
    emit this->chooseBack();
}

void playwindow::gameError(int order)
{
    MyPushButton *num = new MyPushButton(":/new/res/error.png");
    num->setParent(this);
    num->setEnabled(false);
    num->setFixedSize(400, 400);
    num->move(480, 360);
    num->show();
    backBtn->setEnabled(false);
    pNormalLineEdit->setEnabled(false);
    Delay_MSec(3000);
    emit this->chooseBack();
}

void playwindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":new/res/game.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

playwindow::~playwindow()
{
    output_show.clear();
    input.clear();
    output_goal.clear();
    output.clear();

    present = NULL;
    number_order=0;
    for(int i=0; i<3; i++)
    {
        whether_emptyPlace[i] = 1;
        emptyPlace[i] = NULL;
    }
    whether_inbox = 1;
}
