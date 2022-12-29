#include "laser.h"

#include <QPen>
#include <asteroid.h>

#define LASER_SPEED 4
#define LASER_LENGTH 10

Laser::Laser(QPointF initPos, QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    yspeed = LASER_SPEED;
    setPen(QPen(QBrush(Qt::red), 3));
    setLine(0, 0, 0, -LASER_LENGTH);
    setPos(initPos);
}

void Laser::advance(int phase){
    if(phase){
        moveBy(0, -yspeed);
        if(data(0).toBool() || this->y() < 0){
            delete this;
        }
    } else {
        foreach(QGraphicsItem *item, collidingItems()){
            if(item->type() == Asteroid::Type){
                Asteroid* asteroid = qgraphicsitem_cast<Asteroid*>(item);
                asteroid->lifes--;
                if (asteroid->lifes <= 0) {
                    item->setData(0, true);
                }
                setData(0, true);
            }
        }
    }
}
