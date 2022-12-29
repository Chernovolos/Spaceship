#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;
    MainWindow *w;

//signals:
//   void signal();
};

#endif // FORM_H
