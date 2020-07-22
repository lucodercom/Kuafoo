#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Kuafoo.h"

class Kuafoo : public QMainWindow
{
    Q_OBJECT

public:
    Kuafoo(QWidget *parent = Q_NULLPTR);

private:
    Ui::KuafooClass ui;

private slots:
    void on_actionImageFormater_triggered();
};
