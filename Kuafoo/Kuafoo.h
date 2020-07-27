#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Kuafoo.h"
#include <QSettings>

//
#include "views/tools/formater/ToolsFormaterImage.h"
#include "views/tools/formater/ToolsFormaterVideo.h"

class Kuafoo : public QMainWindow
{
    Q_OBJECT

public:
    Kuafoo(QWidget *parent = Q_NULLPTR);
    struct Params
    {
        QSettings* settings;
    }params;
    void closeEvent(QCloseEvent* event);
private:
    Ui::KuafooClass ui;
    ToolsFormaterImage* imgFormaterForm;
    ToolsFormaterVideo* videoFormaterForm;
    void dispose();
private slots:
    void on_actionImageFormater_triggered();
    void on_actionVideoFormater_triggered();
};
