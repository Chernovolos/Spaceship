#include "rules.h"
#include "ui_rules.h"
#include <QScrollArea>

Rules::Rules(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Rules)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setParent(0); // Create TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_PaintOnScreen);

    QLabel *imageLabel = new QLabel;
    QImage image("happyguy.png");
    imageLabel->setPixmap(QPixmap::fromImage(image));

    scroll = new QScrollArea;
    scroll->setBackgroundRole(QPalette::Dark);
    scroll->setWidget(imageLabel);
}

Rules::~Rules()
{
    delete ui;
}

void Rules::on_pushButton_clicked()
{
    // trigger Rules::show
    emit closeRules();
    // close this window
    this->close();
}

