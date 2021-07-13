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

class player : public QLabel
{

signals:

public:
    explicit player(QWidget *parent = 0);
    void setIdleState(QString path);
    void setHealth(int HP);
    int getSpeed();
    int isBusy;

    ~player();
private:
    int HP;
    int walkSpeed;
};

#endif // PLAYER_H
