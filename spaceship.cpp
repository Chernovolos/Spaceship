#include "laser.h"
#include "spaceship.h"

#include <QKeyEvent>
#include <QGraphicsScene>

#define SPACESHIP_SPEED 5

Spaceship::Spaceship(int sceneWidth, int sceneHeight, Game* gameState, QObject* parent): QObject(parent), QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/images/spaceship.png"));
    moveToStartPosition(sceneWidth, sceneHeight);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    this->gameState = gameState;

    connect(gameState, &Game::isPausedChanged, this, &Spaceship::onPause);
    connect(gameState, &Game::isCancelledChanged, this, &Spaceship::onCancel);
}

void Spaceship::advance(int phase)
{
    if(phase){
        moveBy(xspeed, yspeed);


    } else {
//        foreach(QGraphicsItem *item, collidingItems()){
//            if(item->type() == Asteroid::Type) {
//                // signal to mainwindow to remove lifes and possibly end the game
//                gameState->removeLifes(1);
//                item->setData(0, true);
//            }
//        }
   }
}

void Spaceship::moveToStartPosition(int sceneWidth, int sceneHeight){
    setPos(sceneWidth/2 - pixmap().width() / 2 , sceneHeight-pixmap().height() - 50);
    xspeed = 0;
    yspeed = 0;
}

void Spaceship::keyPressEvent(QKeyEvent *event)
{
    if (!gameState->getIsPaused()) {
        switch (event->key()) {
            case Qt::Key_Left:
                if (this->x() - SPACESHIP_SPEED > 0) {
                    xspeed = -SPACESHIP_SPEED;
                }
                break;
            case Qt::Key_Right:
                if (this->x() + SPACESHIP_SPEED < scene()->width() - pixmap().width()) {
                    xspeed= SPACESHIP_SPEED;
                }
                break;
            case Qt::Key_Up:
                if (this->y() - SPACESHIP_SPEED > 0) {
                    yspeed = -SPACESHIP_SPEED;
                }
                break;
            case Qt::Key_Down:
                if (this->y() + SPACESHIP_SPEED < scene()->height() - pixmap().height()) {
                    yspeed = SPACESHIP_SPEED;
                }
                break;
            case Qt::Key_Space:
                scene()->addItem(new Laser(mapToScene(QPointF(pixmap().width()/2, 0)), 0));
                break;
            default:
                break;
        }
    }
}

void Spaceship::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        if (this->x() - SPACESHIP_SPEED < 0)
            setPos(0, y());
        xspeed = 0;
        break;
    case Qt::Key_Right:
        if (this->x() + SPACESHIP_SPEED > scene()->width() - pixmap().width())
            setPos(scene()->width() - pixmap().width(), y());
        xspeed = 0;
        break;
    case Qt::Key_Up:
        if (this->y() - SPACESHIP_SPEED < 0)
            setPos(x(), 0);
        yspeed = 0;
        break;
    case Qt::Key_Down:
        if (this->y() + SPACESHIP_SPEED > scene()->height() - pixmap().height())
            setPos(x(), scene()->height() - pixmap().height());
        yspeed = 0;
        break;
    default:
        break;

    }
}

int Spaceship::type() const
{
    return Type;
}

// on pause (side effects)
void Spaceship::onPause(bool isPaused)
{
    // stop movement on pause
    if(isPaused){
        xspeed = 0;
        yspeed = 0;
    } else {
        this->setFocus();
    }
}

void Spaceship::onCancel(bool isCancel)
{
    // stop movement on pause
    if(isCancel){
        xspeed = 0;
        yspeed = 0;
        this->setFocus();
    } else {
        this->setFocus();
    }
}
