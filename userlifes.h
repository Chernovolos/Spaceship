#ifndef USERLIFES_H
#define USERLIFES_H

#include <QWidget>
#include <QGraphicsPixmapItem>

class UserLifes : public QGraphicsPixmapItem
{
public:
    UserLifes(int position, int sceneWidth);
     // QGraphicsItem interface
    enum {Type = UserType +10};   
    virtual int type() const;

    void changeState(bool newState);


private:
    bool state;
    QPixmap RED_HEART = QPixmap(":/images/life.PNG");
    QPixmap WHITE_HEART = QPixmap(":/images/dead.PNG");
    QPixmap DARK_HEART = QPixmap(":/images/dark_heart.png");
};

#endif // USERLIFES_H
