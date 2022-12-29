#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    w = new MainWindow();

    connect(w, &MainWindow::signal, this, &Form::show);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    w->show();
    this->close();
}

