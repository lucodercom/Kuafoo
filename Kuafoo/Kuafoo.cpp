#include "Kuafoo.h"

#include "views/tools/formater/ToolsFormaterImage.h"

Kuafoo::Kuafoo(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}


void Kuafoo::on_actionImageFormater_triggered() {
	ToolsFormaterImage* formater = new ToolsFormaterImage();
	formater->show();
}