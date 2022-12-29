#ifndef ASTEROID_H
#define ASTEROID_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include "game.h"

class Asteroid : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    enum {Type = UserType + 1};
    int lifes = 1;
    Asteroid(int xspread, Game* gameState, QObject* parent = 0);
    // QGraphicsItem interface
    virtual int type() const;

private:
    int yspeed = 2;
    Game* gameState;


public slots:
    virtual void advance(int phase);

signals:
    void asteroidDeleted(Asteroid* asteroid);
};

#endif // ASTEROID_H
