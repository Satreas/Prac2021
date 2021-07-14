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
    p1PlayAnimation[STATE_IDLE]=new QMovie(":/new/char_img/char/GD/Gor_Idle.gif");
    p1PlayAnimation[STATE_WALK]=new QMovie(":/new/char_img/char/GD/Gor_Walk_Towards.gif");
    p1PlayAnimation[STATE_RETIRE]=new QMovie(":/new/char_img/char/GD/Gor_Walk_Backwards.gif");
    p1PlayAnimation[STATE_PUNCH]=new QMovie(":/new/char_img/char/GD/Gor_Punch.gif");

    connect(p1PlayAnimation[STATE_IDLE],SIGNAL(frameChanged(int)),this,SLOT(P1Moveset(int)));
    connect(p1PlayAnimation[STATE_WALK],SIGNAL(frameChanged(int)),this,SLOT(P1Moveset(int)));
    connect(p1PlayAnimation[STATE_RETIRE],SIGNAL(frameChanged(int)),this,SLOT(P1Moveset(int)));
    connect(p1PlayAnimation[STATE_PUNCH],SIGNAL(frameChanged(int)),this,SLOT(P1Fightset(int)));

    p1State = STATE_IDLE;
    p1PlayAnimation[p1State]->start();
//-----------------------------------------------------------------------------------------------

//------------------------------------------P2-INI-----------------------------------------------
    P2 = new player();
    p2PlayAnimation[STATE_IDLE]=new QMovie(":/new/char_img/char/AK/Aka_Idle.gif");
    p2PlayAnimation[STATE_WALK]=new QMovie(":/new/char_img/char/AK/Aka_Walk.gif");
    p2PlayAnimation[STATE_RETIRE]=new QMovie(":/new/char_img/char/AK/Aka_Retire.gif");

    connect(p2PlayAnimation[STATE_IDLE],SIGNAL(frameChanged(int)),this,SLOT(P2Moveset(int)));
    connect(p2PlayAnimation[STATE_WALK],SIGNAL(frameChanged(int)),this,SLOT(P2Moveset(int)));
    connect(p2PlayAnimation[STATE_RETIRE],SIGNAL(frameChanged(int)),this,SLOT(P2Moveset(int)));

    p2State = STATE_IDLE;
    p2PlayAnimation[p2State]->start();
//-----------------------------------------------------------------------------------------------
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &GameScreen::slotGameTimer);
    timer->start(1000/60);
}

void GameScreen::getP1Pos()
{
    p1Width=ui->p1Model->width()/8.5;
    p1Height=ui->p1Model->height();
    p1PosX=ui->p1Model->x()+ui->p1Model->width()/2-p1Width/2;
    p1PosY=ui->p1Model->y();
}

void GameScreen::getP2Pos()
{
    p2Width=ui->p2Model->width()/5;
    p2Height=ui->p2Model->height();
    p2PosX=ui->p2Model->x()+ui->p2Model->width()/2-p2Width/2;
    p2PosY=ui->p2Model->y();
}

void GameScreen::P1Moveset(int frameNumber)
{
    QPixmap shipPixels=p1PlayAnimation[p1State]->currentPixmap();
    getP1Pos();

//    ui->ShowFrame->setText(QString::number(p1PosX));
    ui->p1Model->setPixmap(shipPixels);
}

void GameScreen::P2Moveset(int frameNumber)
{
    QPixmap shipPixels=p2PlayAnimation[p2State]->currentPixmap();
    ui->p2Model->setPixmap(shipPixels);
    getP2Pos();

    ui->ShowFrame->setText(QString::number(p2PosX));
}

void GameScreen::P1Fightset(int frameNumber)
{
    if(p1State==STATE_PUNCH)
    {
        QPoint pos=ui->p1Model->pos();
        ui->framesRN->setText(QString::number(frameNumber));
        switch (frameNumber)
        {
        case 0:
            if (p1PosX+p1Width<ui->Background->width() && p1PosX+p1Width<p2PosX+p2Width/2)
            {
                pos.setX(pos.x()+5);
                ui->p1Model->move(pos);
            }
            break;
        case 1:
            if (p1PosX+p1Width<ui->Background->width() && p1PosX+p1Width<p2PosX+p2Width/2)
            {
                pos.setX(pos.x()+73);
                ui->p1Model->move(pos);
            }
            break;
        case 2:
            if (p1PosX+p1Width<ui->Background->width() && p1PosX+p1Width<p2PosX+p2Width/2)
            {
                pos.setX(pos.x()+80);
                ui->p1Model->move(pos);
            }
            break;
        case 3:
            if (p1PosX+p1Width<ui->Background->width() && p1PosX+p1Width<p2PosX+p2Width/2)
            {
                pos.setX(pos.x()+10);
                ui->p1Model->move(pos);
            }
            break;
        case 6:
            if (p1PosX+p1Width<ui->Background->width() && p1PosX+p1Width<p2PosX+p2Width/2)
            {
                pos.setX(pos.x()+73);
                ui->p1Model->move(pos);
            }
            break;
        case 7:
            p1PlayAnimation[p1State]->stop();
            P1->isBusy = 0;
            p1State=STATE_IDLE;
            p1PlayAnimation[p1State]->start();
            if (p1PosX+p1Width<ui->Background->width() && p1PosX+p1Width<p2PosX+p2Width/2)
            {
                pos.setX(pos.x()+22);
                ui->p1Model->move(pos);
            }
            break;
        }
    }
}


GameScreen::~GameScreen()
{
    delete ui;
}



void  GameScreen::slotGameTimer()
{
//----------------------P1Keys--------------------------

    if(GetAsyncKeyState('D') && P1->isBusy == 0)
    {
        p1State = STATE_WALK;
        p1PlayAnimation[p1State]->start();
        if (p1PosX+p1Width<ui->Background->width() && p1PosX+p1Width<p2PosX+p2Width/2)
        {
            QPoint pos=ui->p1Model->pos();
            pos.setX(pos.x()+P1->getSpeed());
            ui->p1Model->move(pos);
        }
    }

    if(GetAsyncKeyState('A') && P1->isBusy == 0)
    {
        p1State = STATE_RETIRE;
        p1PlayAnimation[p1State]->start();
        if (p1PosX>ui->Background->x())
        {
            QPoint pos=ui->p1Model->pos();
            pos.setX(pos.x()-P1->getSpeed());
            ui->p1Model->move(pos);
        }
    }

    if(GetAsyncKeyState('J') && P1->isBusy == 0)
    {
        p1State = STATE_PUNCH;
        P1->isBusy=1;
        p1PlayAnimation[p1State]->start();
    }

//----------------------P2Keys--------------------------

    if(GetAsyncKeyState(VK_RIGHT) && P2->isBusy == 0)
    {
        p2State = STATE_RETIRE;
        p2PlayAnimation[p2State]->start();
        if (p2PosX+p2Width<ui->Background->width())
        {
            QPoint pos=ui->p2Model->pos();
            pos.setX(pos.x()+P2->getSpeed());
            ui->p2Model->move(pos);
        }
    }

    if(GetAsyncKeyState(VK_LEFT) && P2->isBusy == 0)
    {
        p2State = STATE_WALK;
        p2PlayAnimation[p2State]->start();
        if (p2PosX>ui->Background->x() && p2PosX>p1PosX+p1Width/2)
        {
            QPoint pos=ui->p2Model->pos();
            pos.setX(pos.x()-P2->getSpeed());
            ui->p2Model->move(pos);
        }
    }
}


void GameScreen::keyReleaseEvent(QKeyEvent *ev)
{
//----------------------P1Keys--------------------------
    switch (ev->key())
    {
    case Qt::Key_A:
        if(GetAsyncKeyState('A')==NULL && P1->isBusy==0)
            p1State = STATE_IDLE;
        break;

    case Qt::Key_D:
        if(GetAsyncKeyState('D')==NULL && P1->isBusy==0)
            p1State = STATE_IDLE;
        break;
//----------------------P2Keys--------------------------
    case Qt::Key_Right:
        if(GetAsyncKeyState(VK_RIGHT)==NULL && P1->isBusy==0)
            p2State = STATE_IDLE;
        break;
    case Qt::Key_Left:
        if(GetAsyncKeyState(VK_LEFT)==NULL && P1->isBusy==0)
            p2State = STATE_IDLE;
        break;
    }
}


