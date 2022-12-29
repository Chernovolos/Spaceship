#ifndef SPRITE_H
#define SPRITE_H

#include <QTimer>
#include <QPixmap>
#include <QObject>
#include <QPainter>
#include <QGraphicsItem>

class Sprite : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite(QPointF point, QObject *parent = 0);
    enum { Type = UserType + 3 };
    int type() const;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QTimer *timer;  // Explosion animation timer
    QPixmap *spriteImage;   // QPixmap for explosion sprite
    int currentFrame;   // The coordinate of the current frame in the sprite

private slots:
    void nextFrame();   // Frame flip slot
};

#endif // SPRITE_H
