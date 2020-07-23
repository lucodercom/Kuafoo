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
	QString current = "F:/数据/图像数据/高分四号/多光谱/0.tiff";
	std::vector<cv::Mat> matrixs = helper.readImageIntoMatrixVectorWithGDAL(current,3);

	//给每一个波段归一化
	/*
	cv::Mat matrix = currentMatrix / 8;*/
	std::vector<cv::Mat> resultMatrixs;

	for (size_t i = 0; i < matrixs.size(); i++)
		matrixs[i] = helper.convert28UMatrix(matrixs[i]);

	cv::Mat result;
	cv::merge(matrixs, result);

	cv::imwrite("a.bmp", result);

	//判断波段

}

void ToolsFormaterImage::on_pbCancle_clicked()
{
}
