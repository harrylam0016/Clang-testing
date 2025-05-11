#define QT_MOC_INCLUSION
#include "Clangtesting.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Clangtesting w;
    w.show();
    return a.exec();
}
