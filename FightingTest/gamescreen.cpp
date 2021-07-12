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
    QMovie *movie = new QMovie(":/new/char_img/char/GD/GordeauIdle.gif");
    ui->p1Model->setMovie(movie);
    movie->start();
}


GameScreen::~GameScreen()
{
    delete ui;
}

void  GameScreen::keyPressEvent(QKeyEvent *ev)
{

    QPoint pos=ui->p1Model->pos();
    switch (ev->key())
    {
    case Qt::Key_Right:
        pos.setX(pos.x()+5);
        ui->p1Model->move(pos);
        break;
    }
}

void GameScreen::keyReleaseEvent(QKeyEvent *ev)
{
}



