#include "initmainwindow.h"
#include "ui_initmainwindow.h"

InitMainWindow::InitMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InitMainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(850, 650);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setParent(0); // Create TopLevel-Widget
//    setAttribute(Qt::WA_NoSystemBackground, true);
//    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_PaintOnScreen);

    QPixmap bkgnd(":/images/space.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    game = new GameWindow();

    rules = new Rules();
    connect(game, &GameWindow::gameFinished, this, &InitMainWindow::show);
    connect(rules, &Rules::closeRules, this, &InitMainWindow::show);
}

InitMainWindow::~InitMainWindow()
{
    delete ui;
}

void InitMainWindow::on_pushButton_clicked()
{
   game->show();
   this->close();
}


void InitMainWindow::on_pushButton_2_clicked()
{
    rules->show();
    this->close();
}

void InitMainWindow::on_pushButton_3_clicked()
{
  this->close();
}

