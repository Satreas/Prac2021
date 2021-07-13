#include "gamescreen.h"
#include "ui_gamescreen.h"
#include "player.h"

GameScreen::GameScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);
    this->resize(1280,720);
    this->setFixedSize(1280,720);
//------------------------------------------P1-INI-----------------------------------------------
    P1 = new player();
    p1PlayAnimation[P1_STATE_IDLE]=new QMovie(":/new/char_img/char/GD/Gor_Idle.gif");
    p1PlayAnimation[P1_STATE_WALK]=new QMovie(":/new/char_img/char/GD/Gor_Walk_Towards.gif");
    p1PlayAnimation[P1_STATE_RETIRE]=new QMovie(":/new/char_img/char/GD/Gor_Walk_Backwards.gif");
    p1PlayAnimation[P1_STATE_PUNCH]=new QMovie(":/new/char_img/char/GD/Gor_Punch.gif");

    connect(p1PlayAnimation[P1_STATE_IDLE],SIGNAL(frameChanged(int)),this,SLOT(P1Moveset(int)));
    connect(p1PlayAnimation[P1_STATE_WALK],SIGNAL(frameChanged(int)),this,SLOT(P1Moveset(int)));
    connect(p1PlayAnimation[P1_STATE_RETIRE],SIGNAL(frameChanged(int)),this,SLOT(P1Moveset(int)));
    connect(p1PlayAnimation[P1_STATE_PUNCH],SIGNAL(frameChanged(int)),this,SLOT(P1Moveset(int)));

    p1State = P1_STATE_IDLE;
    p1PlayAnimation[p1State]->start();
//-----------------------------------------------------------------------------------------------
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &GameScreen::slotGameTimer);
    timer->start(1000/60);
}

void GameScreen::P1Moveset(int frameNumber)
{
    QPixmap shipPixels=p1PlayAnimation[p1State]->currentPixmap();

    QPainter p1;
    p1.setRenderHint(QPainter::Antialiasing);
    ui->p1Model->setPixmap(shipPixels);
    ui->framesRN->setText(QString::number(frameNumber));
    if(p1State==P1_STATE_PUNCH)
    {
        int count=p1PlayAnimation[p1State]->frameCount();
        ui->ShowFrame->setText(QString::number(count));
        if(frameNumber==(count))
        {
          ui->ShowFrame->setText("done!");
          p1PlayAnimation[p1State]->stop();
          P1->isBusy = 0;
          p1State=P1_STATE_IDLE;
          p1PlayAnimation[p1State]->start();
          ui->ShowFrame->setText("press again");
         }
    }
}


GameScreen::~GameScreen()
{
    delete ui;
}



void  GameScreen::slotGameTimer()
{

    if(GetAsyncKeyState('D') && P1->isBusy == 0)
    {
        p1State = P1_STATE_WALK;
        p1PlayAnimation[p1State]->start();
        QPoint pos=ui->p1Model->pos();
        pos.setX(pos.x()+P1->getSpeed());
        ui->p1Model->move(pos);
    }

    if(GetAsyncKeyState('A') && P1->isBusy == 0)
    {
        p1State = P1_STATE_RETIRE;
        p1PlayAnimation[p1State]->start();
        QPoint pos=ui->p1Model->pos();
        pos.setX(pos.x()-P1->getSpeed());
        ui->p1Model->move(pos);
    }

    if(GetAsyncKeyState('J') && P1->isBusy == 0)
    {
        p1State = P1_STATE_PUNCH;
        P1->isBusy=1;
        p1PlayAnimation[p1State]->start();
    }
}

void GameScreen::keyReleaseEvent(QKeyEvent *ev)
{
    switch (ev->key())
    {
    case Qt::Key_A:
        if(GetAsyncKeyState('A')==NULL && P1->isBusy==0)
            p1State = P1_STATE_IDLE;
        break;

    case Qt::Key_D:
        if(GetAsyncKeyState('D')==NULL && P1->isBusy==0)
            p1State = P1_STATE_IDLE;
        break;
    }
}

