#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QShortcut>
#include <QPainter>
#include <QMovie>
#include <QTimer>
#include <QEvent>

#include <player.h>

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

private:
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
    Ui::GameScreen *ui;
    QTimer         *timer;
    player         *P1;
};
#endif // GAMESCREEN_H
