#ifndef RULES_H
#define RULES_H

#include <QLabel>
#include <QScrollArea>
#include <QMainWindow>
#include <QGraphicsItem>

namespace Ui {
class Rules;
}

class Rules : public QMainWindow
{
    Q_OBJECT

public:
    explicit Rules(QWidget *parent = nullptr);
    ~Rules();

private:
    Ui::Rules *ui;
    QScrollArea* scroll;
    QLabel *textRules;

signals:
    void closeRules();

private slots:
    void on_pushButton_clicked();
};

#endif // RULES_H
