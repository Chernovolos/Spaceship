#include "gamewindow.h"
#include "initmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitMainWindow w;
    w.show();

    return a.exec();
}
