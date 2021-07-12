#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <QPoint>
#include <QString>
#include <QMovie>
#include <QTimer>
#include <QPainter>
#include <QObject>
#include <QGraphicsItem>

#include <windows.h>

enum player_states
{
    STATE_IDLE=0,
    STATE_WALK=1,
};

class player : public QLabel
{

signals:

public:
    explicit player(QWidget *parent = 0);
    void setIdleState(QString path);
    void setHealth(int HP);
    void setSpeed(int mSpeed);

    ~player();
private:
    int HP;
    int mSpeed;
    int walkSpeed;
    QMovie *statesMovie[2];
};

#endif // PLAYER_H
