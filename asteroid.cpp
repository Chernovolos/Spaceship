#include "sprite.h"
#include "asteroid.h"
#include "spaceship.h"
#include <QGraphicsScene>

#define CIRCLE_SIZE 50

Asteroid::Asteroid(int xspread, Game* gameState, QObject* parent): QObject(parent), QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/images/asteroid.png"));
    setPos(rand()%(xspread - pixmap().width()), 0);
    this->gameState = gameState;
}

void Asteroid::advance(int phase)
{
    if(phase) {
        moveBy(0, yspeed);
        // laser set data(0, true), there were a collision and we should delete it
        if(data(0).toBool()) {
            scene()->addItem(new Sprite(this->pos()));
            /*w->addScore(100);*/
            gameState->addScore(100);

            emit asteroidDeleted(this);
            gameState->pieces.remove(this);
            delete this;

        } else if (this->y() > scene()->height()) {
            emit asteroidDeleted(this);
            gameState->pieces.remove(this);
            delete this;
        }
    } else {
        foreach(QGraphicsItem *item, collidingItems()) {
            if(item->type() == Spaceship::Type) {
                // copy lifes value to local scope in terms of "this" will be deleted during Game::reset
                int isLastLife = gameState->getLifes();
                // signal to mainwindow to remove lifes and possibly end the game
                gameState->removeLifes(1);

                // after loosing last life we clearing all the asteroids in gameState
                if (isLastLife != 1) {
                    emit asteroidDeleted(this);
                    gameState->pieces.remove(this);
                    delete this;
                }
            }
        }
    }
}

int Asteroid::type() const
{
    return Type;
}

