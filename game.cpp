#include "game.h"

Game::Game() : QObject(0)
{
    score = 0;
    lifes = 3;
    pieces = QSet<QGraphicsPixmapItem*>();
}

Game::~Game()
{
//    foreach (QGraphicsPixmapItem* piece, pieces) {
//        delete piece;
//    }
    pieces.clear();
}

int Game::getScore()
{
    return score;
}

int Game::getLifes()
{
    return lifes;
}

void Game::addScore(int scoreAmount)
{
    score += scoreAmount;

    emit scoreChanged(score);
}

void Game::addLifes(int lifesAmount)
{
    lifes += lifesAmount;

    emit lifesChanged(lifes);
}

void Game::removeLifes(int lifesAmount)
{
    lifes -= lifesAmount;

    emit lifesChanged(lifes);
}

void Game::reset()
{
    score = 0;
    lifes = 3;

    emit lifesChanged(lifes);
    emit scoreChanged(score);
    // delete all the asteroids
    qDeleteAll(pieces);
    pieces.clear();
}

void Game::pauseGame(bool pause)
{
   isPaused = pause;

   emit isPausedChanged(isPaused);
}

bool Game::getIsPaused()
{
    return isPaused;
}

void Game::cancelGame(bool cancel)
{
   isCancel = cancel;

   emit isCancelledChanged(isPaused);
}

bool Game::getIsCancelled()
{
    return isCancel;
}
