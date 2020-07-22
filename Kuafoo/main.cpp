#include "Kuafoo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kuafoo w;
    w.show();
    return a.exec();
}
