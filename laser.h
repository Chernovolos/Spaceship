#ifndef LASER_H
#define LASER_H

#include <QGraphicsLineItem>

class Laser : public QGraphicsLineItem
{
public:
    Laser(QPointF initPos, QGraphicsItem *parent);
private:
    int yspeed;

    // QGraphicsItem interface
public:
    virtual void advance(int phase);
};

#endif // LASER_H
