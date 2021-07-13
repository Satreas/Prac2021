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
    P1_STATE_IDLE = 0,
    P1_STATE_WALK = 1,
    P1_STATE_RETIRE = 2,
    P1_STATE_PUNCH = 5
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
    void keyReleaseEvent(QKeyEvent *ev);

private:
    Ui::GameScreen *ui;
    QTimer         *timer;
    QMovie         *p1PlayAnimation[10];
    player         *P1;

    int p1State;
};
#endif // GAMESCREEN_H
