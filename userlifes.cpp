#include <iostream>

#include "userlifes.h"

#include <QGraphicsScene>

UserLifes::UserLifes(int position, int sceneWidth): QGraphicsPixmapItem(0)
{
    state = true;

    if (state) {
        setPixmap(RED_HEART);
    } else {
        setPixmap(WHITE_HEART);
    }
    if (position == 1) {
        setPos(sceneWidth - pixmap().width(), 0);

    } else if (position == 2) {
        setPos(sceneWidth- 2 * pixmap().width() - 5, 0);

    } else if (position == 3) {
        setPos(sceneWidth - 3 * pixmap().width() - 10, 0);
    }
}

void UserLifes::changeState(bool newState)
{
    state = newState;

    if (state) {
        setPixmap(RED_HEART);
    } else {
        setPixmap(WHITE_HEART);
    }
}

int UserLifes::type() const{
    return Type;
}
