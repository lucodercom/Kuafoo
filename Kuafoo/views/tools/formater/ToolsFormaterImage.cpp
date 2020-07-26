#include "ToolsFormaterImage.h"
#include <QFileDialog>
#include <QStandardItem>
#include "../../../common/ImageHelper.h"

ToolsFormaterImage::ToolsFormaterImage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ToolsFormaterImage::~ToolsFormaterImage()
{
}

void ToolsFormaterImage::on_pbScan_clicked()
{
	QDir dir(QFileDialog::getExistingDirectory(this, "选择目录", "./"));

	if (dir.exists()) {
		ui.leSrcFolder->setText(dir.path());

		auto list = dir.entryList();
		QStandardItemModel* ItemModel = new QStandardItemModel();

		for (int i = 0; i < list.size(); i++)
			if (list.at(i) == "." || list.at(i) == "..")
				continue;
			else
				ItemModel->appendRow(new QStandardItem(list.at(i)));
		ui.lsvFiles->setModel(ItemModel);
	}
	else logInfo("指定目录不存在！");
}

void ToolsFormaterImage::logInfo(QString info)
{
	ui.labInfo->setText(info);
}

void ToolsFormaterImage::on_pbAdd_clicked()
{
}

void ToolsFormaterImage::on_pbDel_clicked()
{
}

void ToolsFormaterImage::on_pbSaveFolder_clicked()
{
	ui.leOutput->setText(QFileDialog::getExistingDirectory(this, "选择目录", "./"));
}

void ToolsFormaterImage::on_pbSubmit_clicked()
{
	//注意一个前提，（假设）所有高光谱图像默认为前三个波段为色彩波段，后面波段是其他信息波段，所以这里保存只保存vector中的前三个波段。
	ImageHelper helper;
	//QString current = "F:/数据/图像数据/高分四号/单波段/pic/00.tif";
	QString current = ui.leSrcFolder->text();
	if (current.isEmpty()) {
		logInfo("输入路径不能为空！");
		return;
	}
	QString savePath = ui.pbSaveFolder->text();
	if (current.isEmpty()) {
		logInfo("保存路径不能为空！");
		return;
	}
	QString ext = "jpg";
	ext = ui.cbxFormat->currentText().isEmpty() ? "jpg" : ui.cbxFormat->currentText();

	//读取所有文件
	QString sel = ui.lsvFiles->currentIndex().data().toString();
	if (sel.isEmpty()) {
		logInfo("未选择任何文件！");
		return;
	}
	current = QString("%1/%2").arg(current, sel);
	std::vector<cv::Mat> matrixs = helper.readImageIntoMatrixVectorWithGDAL(current,3);
	//给每一个波段归一化
	for (size_t i = 0; i < matrixs.size(); i++)
		matrixs[i] = helper.convert28UMatrix(matrixs[i]);

	cv::Mat result;
	cv::merge(matrixs, result);
	
	savePath = QString("%1.%2").arg(savePath,ext);
	if (cv::imwrite(savePath.toStdString(), result))
		logInfo("OK");
	else
		logInfo("Error");

	//判断波段

}

void ToolsFormaterImage::on_pbCancle_clicked()
{
}
