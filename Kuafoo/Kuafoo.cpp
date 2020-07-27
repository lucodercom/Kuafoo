#include "Kuafoo.h"


Kuafoo::Kuafoo(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}


void Kuafoo::on_actionImageFormater_triggered() {
	imgFormaterForm = new ToolsFormaterImage();
	imgFormaterForm->show();
}

void Kuafoo::closeEvent(QCloseEvent* event)
{
	dispose();
}

void Kuafoo::dispose()
{
	if (nullptr != imgFormaterForm) 
		imgFormaterForm->close();
	
	if (nullptr != videoFormaterForm)
		videoFormaterForm->close();
}

void Kuafoo::on_actionVideoFormater_triggered()
{
	videoFormaterForm = new ToolsFormaterVideo();
	videoFormaterForm->show();
}
