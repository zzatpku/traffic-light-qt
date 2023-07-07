#include "mainscene.h"
#include "dialog2.h"
#include "mainwindowdyx.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowDyx x;
    QDesktopWidget *desktop = QApplication::desktop();
    x.move((desktop->width() - 1723)/ 2, (desktop->height() - 1076) /2);
    x.show();
    return a.exec();
}
