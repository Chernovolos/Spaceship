#include "sprite.h"

Sprite::Sprite(QPointF point, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(point);    // Set the position of the explosion
    currentFrame = 0;       // The X coordinate of the start of the bullet explosion
    spriteImage = new QPixmap(":/images/sprite_sheet.png");
    timer = new QTimer();   // Initializing the explosion animation timer
    // Connect the signal from the timer to the explosion animation slot
    connect(timer, &QTimer::timeout, this, &Sprite::nextFrame);
    timer->start(30);
}

QRectF Sprite::boundingRect() const
{
    return QRectF(15, 15, 40, 40);
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Draw one of the frames of the explosion
    painter->drawPixmap(15, 15, *spriteImage, currentFrame, 0, 20, 20);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Sprite::nextFrame()
{
    currentFrame += 20; // Advance the X coordinate to select the next frame
    if (currentFrame >= 300 ) {
        this->deleteLater(); // If the frames are over, then delete the object of the explosion
    } else {
        this->update(15, 15, 20, 20); // Otherwise, update the graphic object
    }
}

int Sprite::type() const {
    // Returning the object type
    return Type;
}
