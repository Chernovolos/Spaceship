#ifndef INITMAINWINDOW_H
#define INITMAINWINDOW_H

#include "rules.h"
#include "gamewindow.h"

#include <QMainWindow>

namespace Ui {
class InitMainWindow;
}

class InitMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InitMainWindow(QWidget *parent = nullptr);
    ~InitMainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::InitMainWindow *ui;
    GameWindow *game;
    Rules *rules;
};

#endif // INITMAINWINDOW_H
