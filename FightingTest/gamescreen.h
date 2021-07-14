#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QShortcut>
#include <QPainter>
#include <QMovie>
#include <QThread>
#include <QTimer>
#include <QKeyEvent>

#include <player.h>

enum Players_States
{
    STATE_IDLE = 0,
    STATE_WALK = 1,
    STATE_RETIRE = 2,
    STATE_PUNCH = 5
};

QT_BEGIN_NAMESPACE
namespace Ui { class GameScreen; }
QT_END_NAMESPACE

class GameScreen : public QMainWindow
{
    Q_OBJECT

public:
    GameScreen(QWidget *parent = nullptr);
    ~GameScreen();

private slots:
    void slotGameTimer();
    void P1Moveset(int frameNumber);
    void P1Fightset(int frameNumber);
    void getP1Pos();

    void P2Moveset(int frameNumber);
    void getP2Pos();
    void keyReleaseEvent(QKeyEvent *ev);

private:
    Ui::GameScreen *ui;
    QTimer         *timer;
    QMovie         *p1PlayAnimation[10];
    player         *P1;
    int p1State;
    int p1Multiplier;
    int p1Width; int p1Height; int p1PosX; int p1PosY;

    player         *P2;
    QMovie         *p2PlayAnimation[10];
    int p2State;
    int p2Width; int p2Height; int p2PosX; int p2PosY;
};
#endif // GAMESCREEN_H
