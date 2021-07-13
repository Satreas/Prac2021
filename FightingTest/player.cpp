#include "player.h"
#include "gamescreen.h"

player::player(QWidget *parent) : QLabel(parent)
{
    isBusy=0;
    walkSpeed=4;
}

player::~player()
{

}

int player::getSpeed()
{
    return  walkSpeed;
}
