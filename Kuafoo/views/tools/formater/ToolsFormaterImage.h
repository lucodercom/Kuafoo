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
private slots:
	void on_pbScan_clicked();
	void on_pbAdd_clicked();
	void on_pbDel_clicked();
	void on_pbSaveFolder_clicked();
	void on_pbSubmit_clicked();
	void on_pbCancle_clicked();

	//
	
};
