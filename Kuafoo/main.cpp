#include "Kuafoo.h"
#include <QtWidgets/QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kuafoo w;
    QSettings settings(":/Rmcp/config.ini",QSettings::IniFormat);
    w.params.settings = &settings;

    w.show();
    return a.exec();
}
