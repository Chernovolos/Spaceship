#ifndef GAME_H
#define GAME_H

#include <QSet>
#include <QObject>
#include <QGraphicsPixmapItem>

class Game : public QObject
{
    Q_OBJECT

public:
    QSet<QGraphicsPixmapItem*> pieces;
    Game();
    ~Game();
    void reset();
    int getScore();
    int getLifes();
    bool getIsPaused();
    bool getIsCancelled();

private:
    int score;
    int lifes;
    bool isPaused = false;
    bool isCancel = false;

public slots:
    void pauseGame(bool pause);
    void cancelGame(bool pause);
    void addScore(int scoreAmount);
    void addLifes(int lifesAmount);
    void removeLifes(int lifesAmount);

signals:
    void scoreChanged(int score);
    void lifesChanged(int lifes);
    void isPausedChanged(bool isPause);
    void isCancelledChanged(bool isCancel);
};

#endif // GAME_H
