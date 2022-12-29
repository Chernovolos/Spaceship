#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "game.h"
#include "spaceship.h"
#include "userlifes.h"

#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>


QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void onGenerate();
    void onPauseClick();
    void onCancelClick();
    void initializeGame();
    void drawLifes(int lifes);
    void drawScore(int points);
    void onPause(bool isPaused);


private:
    Ui::GameWindow *ui;
    QGraphicsScene *scene;

    QTimer *animationTimer;
    QTimer *generatorTimer;

    QPushButton *pauseBtn;
    QPushButton *cancelBtn;

    Game* gameState;

    QGraphicsSimpleTextItem *scoreLable;
    QGraphicsSimpleTextItem *startLable;

    UserLifes* life1;
    UserLifes* life2;
    UserLifes* life3;

    Spaceship* spaceship;

    bool isInitialized = false;

    void clearGame();
    void removeFromScene(QGraphicsItem *item);

signals:
    void gameFinished();

};
#endif // GAMEWINDOW_H
