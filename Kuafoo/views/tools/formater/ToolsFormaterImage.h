#pragma once

#include <QWidget>
#include "ui_ToolsFormaterImage.h"
#include "../../../controllers/tools/formater/ToolsFormaterImageController.h"

class ToolsFormaterImage : public QWidget
{
	Q_OBJECT

public:
	ToolsFormaterImage(QWidget *parent = Q_NULLPTR);
	~ToolsFormaterImage();

private:
	Ui::ToolsFormaterImage ui;
	ToolsFormaterImageController* controller;
};
