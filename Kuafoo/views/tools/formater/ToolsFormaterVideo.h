#pragma once

#include <QWidget>
#include "ui_ToolsFormaterVideo.h"

class ToolsFormaterVideo : public QWidget
{
	Q_OBJECT

public:
	ToolsFormaterVideo(QWidget *parent = Q_NULLPTR);
	~ToolsFormaterVideo();

private:
	Ui::ToolsFormaterVideo ui;
};
