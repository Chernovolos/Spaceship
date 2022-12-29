#ifndef FALLINGCIRCLE_H
#define FALLINGCIRCLE_H

#include <QWidget>
#include <QGraphicsEllipseItem>

class FallingCircle: public QGraphicsEllipseItem
{
public:
    FallingCircle(int xspread);
private:
   int yspeed = 1;

   // QGraphicsItem interface
public:
   virtual void advance(int phase);

   // QGraphicsItem interface
protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // FALLINGCIRCLE_H
