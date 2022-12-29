#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "game.h"

#include <QWidget>
#include <QGraphicsPixmapItem>

class Spaceship: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Spaceship(int sceneWidth, int sceneHeight, Game* gameState, QObject* parent = 0);
    enum {Type = UserType +2};
    // QGraphicsItem interface
    virtual void advance(int phase);
    virtual int type() const;
    void moveToStartPosition(int sceneHeight, int sceneWidth);


protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    int xspeed = 0;
    int yspeed = 0;
    int lifes = 3;
    Game* gameState;

public slots:
    void onPause(bool isPaused);
    void onCancel(bool isPaused);
};

#endif // SPACESHIP_H
