#include "fallingcircle.h"

#define CIRCLE_SIZE 50

FallingCircle::FallingCircle(int xspread): QGraphicsEllipseItem(0)
{
   QColor color = QColor(rand()%255, rand()%255, rand()%255);
   setBrush(color);
   setRect(0, 0, 50, 50);
   setPos(rand()%(xspread - 50), 0);
}

void FallingCircle::advance(int phase){
    if(phase){
        moveBy(0, yspeed);
    }
}

void FallingCircle::mousePressEvent(QGraphicsSceneMouseEvent *event){
    delete this;
}
