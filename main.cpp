#include "Mainscene.h"
#include "Dialog2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog2 x;
    x.show();
    return a.exec();
}
