#include <iostream>

#include "game.h"
#include "asteroid.h"
#include "userlifes.h"
#include "spaceship.h"
#include "gamewindow.h"
#include "ui_mainwindow.h"
#include "fallingcircle.h"

#include <QFont>
#include <QLabel>
#include <QColor>
#include <QtGlobal>
#include <QMessageBox>
#include <QGraphicsSimpleTextItem>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setParent(0); // Create TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_PaintOnScreen);

    scene = new QGraphicsScene(0, 0, 800, 600, this);
    scene->setStickyFocus(true);
    ui->graphicsView->setScene(scene);
}

GameWindow::~GameWindow()
{
    clearGame();

    delete ui;
}

void GameWindow::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );

    if (!isInitialized) {
        initializeGame();
        isInitialized = true;
    } else {
        clearGame();
    }
}

void GameWindow::drawLifes(int lifes)
{
    // draw lifes icons depending on lifes value[0;3]
    if(lifes == 3) {
        life1->changeState(true);
        life2->changeState(true);
        life3->changeState(true);

    } else if (lifes == 2) {
        life1->changeState(false);
        life2->changeState(true);
        life3->changeState(true);
    } else if (lifes == 1) {
        life1->changeState(false);
        life2->changeState(false);
        life3->changeState(true);
    } else if (lifes == 0) {
        life1->changeState(false);
        life2->changeState(false);
        life3->changeState(false);

        std::cout << "Game Over" << std::endl;

        // stop generation and animation timers in case of Game Over
        generatorTimer->stop();
        animationTimer->stop();

        QString resultScore = QString::number(gameState->getScore());
        QMessageBox* msgBox = new QMessageBox();
        msgBox->setGeometry(800, 500, 300, 300);
        msgBox->resize(500, 500);
        msgBox->setWindowFlag(Qt::FramelessWindowHint);
        msgBox->setCursor(Qt::PointingHandCursor);
        msgBox->setText("GAME OVER");
        msgBox->setInformativeText("Score: " + resultScore +
                                   "\n\nDo you want to restart the game or go to the main menu?");

        msgBox->setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
        msgBox->setButtonText(QMessageBox::Retry, "Restart");
        msgBox->setButtonText(QMessageBox::Close, "Main Menu");
        msgBox->setStyleSheet("background-color: black; "
                              "color : rgb(255, 255, 0); "
                              "border-radius: 5px; "
                              "font: 13pt 'MS Gothic'; "
                              "border-color: rgb(255, 255, 0); "
//                              "border: 3px solid rgb(255, 255, 0); "
                              "padding: 10px;"
                              "qproperty-centerButtons: true;");
        int ret = msgBox->exec();

        switch (ret) {
          case QMessageBox::Retry:
              // Ok was clicked
            clearGame();
            break;
          case QMessageBox::Close:
            // TODO save score in records
            int score = gameState->getScore();
            std::cout << "Go to main window clicked. Score: " << score << std::endl;

            // trigger InitialMainWindow::show
            emit gameFinished();
            // close this window
            this->close();
            break;
        }
    }
}

void GameWindow::drawScore(int scoreValue)
{
    QString result = QString::number(scoreValue);
    if (scoreValue <= 0) {
        result = "00000";
    } else if (scoreValue < 10){
        result = "0000" + result;
    } else if (scoreValue < 100) {
        result = "000" + result;
    } else if (scoreValue < 1000) {
        result = "00" + result;
    } else if (scoreValue < 10000) {
        result = "0" + result;
    }

    scoreLable->setText(result);
}

void GameWindow::onGenerate()
{
    Asteroid* asteroid = new Asteroid(scene->sceneRect().width(), gameState);
    gameState->pieces.insert(asteroid);
    scene->addItem(asteroid);
    connect(asteroid, &Asteroid::asteroidDeleted, this, &GameWindow::removeFromScene);
}

void GameWindow::initializeGame()
{
    // setup score ui
    scoreLable = new QGraphicsSimpleTextItem("");
    scoreLable->setPos(350, 0);
    scoreLable->setFont(QFont("Arial", 20));
    scoreLable->setBrush(QColor::fromRgb(255, 223, 0));
    scene->addItem(scoreLable);

    // setup lifes ui
    life1 = new UserLifes(1, scene->width());
    scene->addItem(life1);
    life2 = new UserLifes(2, scene->width());
    scene->addItem(life2);
    life3 = new UserLifes(3, scene->width());
    scene->addItem(life3);

    // setup pause btn
    pauseBtn = new QPushButton();
    pauseBtn->setIcon(QIcon(":/images/pause.png"));
    pauseBtn->setGeometry(QRect(0, 0, 60, 60));
    pauseBtn->setIconSize(QSize(50, 50));
    pauseBtn->setCursor(Qt::PointingHandCursor);

    pauseBtn->setStyleSheet("background-color: transparent;");
    scene->addWidget(pauseBtn);
    connect(pauseBtn, &QPushButton::clicked, this, &GameWindow::onPauseClick);

    // setup pause close
    cancelBtn = new QPushButton();
    cancelBtn->setIcon(QIcon(":/images/cancel.png"));
    cancelBtn->setGeometry(QRect(60, 0, 60, 60));
    cancelBtn->setIconSize(QSize(60, 60));
    cancelBtn->setCursor(Qt::PointingHandCursor);

    cancelBtn->setStyleSheet("background-color: transparent;");
    scene->addWidget(cancelBtn);
    connect(cancelBtn, &QPushButton::clicked, this, &GameWindow::onCancelClick);


    // setup game state
    gameState = new Game();
    // subscribe on lifes and score changes to redraw their representation
    connect(gameState, &Game::scoreChanged, this, &GameWindow::drawScore);
    connect(gameState, &Game::lifesChanged, this, &GameWindow::drawLifes);
    connect(gameState, &Game::isPausedChanged, this, &GameWindow::onPause);

    // render initial score and lifes
    drawScore(gameState->getScore());
    drawLifes(gameState->getLifes());

    // setup spaceship
    spaceship = new Spaceship(scene->width(), scene->height(), gameState);
    scene->addItem(spaceship);

    // setup animation timer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, scene, &QGraphicsScene::advance);

    // setup generation timer
    generatorTimer =  new QTimer(this);
    connect(generatorTimer, &QTimer::timeout, this, &GameWindow::onGenerate);

    // start animation and generation of obsticles
    animationTimer->start(1000/60);
    generatorTimer->start(1000);
}

void GameWindow::clearGame()
{
    gameState->reset();
    spaceship->moveToStartPosition(scene->width(), scene->height());
    ui->graphicsView->viewport()->update();

    animationTimer->start(1000/60);
    generatorTimer->start(1000);
}

void GameWindow::removeFromScene(QGraphicsItem *item)
{
    scene->removeItem(item);
}

// on pause click (button click listener)
void GameWindow::onPauseClick()
{
    gameState->pauseGame(!gameState->getIsPaused());
}

// on pause (side effects)
void GameWindow::onPause(bool isPaused)
{
    // stop animation
    if(isPaused) {
        generatorTimer->stop();
        animationTimer->stop();
        pauseBtn->setIcon(QIcon(":/images/play.png"));
    } else {
        generatorTimer->start(1000);
        animationTimer->start(1000/60);
        pauseBtn->setIcon(QIcon(":/images/pause.png"));
    }
}

void GameWindow::onCancelClick()
{
    gameState->cancelGame(!gameState->getIsPaused());
    int score = gameState->getScore();
    std::cout << "Go to main window clicked. Score: " << score << std::endl;

     clearGame();
    // trigger InitialMainWindow::show
    emit gameFinished();
    // close this window
    this->close();
}
