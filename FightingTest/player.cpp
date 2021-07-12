#include "player.h"
#include "gamescreen.h"

player::player(QWidget *parent) : QLabel(parent)
{
    HP=10000;
    mSpeed=0;

}

player::~player()
{

}

void player::setIdleState(QString path)
{
    statesMovie[STATE_IDLE]=new QMovie(path);
}
