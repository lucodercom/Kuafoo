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
	QDir dir(QFileDialog::getExistingDirectory(this, "ѡ��Ŀ¼", "./"));

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
	else logInfo("ָ��Ŀ¼�����ڣ�");
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
	ui.leOutput->setText(QFileDialog::getExistingDirectory(this, "ѡ��Ŀ¼", "./"));
}

void ToolsFormaterImage::on_pbSubmit_clicked()
{
	//ע��һ��ǰ�ᣬ�����裩���и߹���ͼ��Ĭ��Ϊǰ��������Ϊɫ�ʲ��Σ����沨����������Ϣ���Σ��������ﱣ��ֻ����vector�е�ǰ�������Ρ�
	ImageHelper helper;
	//QString current = "F:/����/ͼ������/�߷��ĺ�/������/pic/00.tif";
	QString current = ui.leSrcFolder->text();
	if (current.isEmpty()) {
		logInfo("����·������Ϊ�գ�");
		return;
	}
	QString savePath = ui.pbSaveFolder->text();
	if (current.isEmpty()) {
		logInfo("����·������Ϊ�գ�");
		return;
	}
	QString ext = "jpg";
	ext = ui.cbxFormat->currentText().isEmpty() ? "jpg" : ui.cbxFormat->currentText();

	//��ȡ�����ļ�
	QString sel = ui.lsvFiles->currentIndex().data().toString();
	if (sel.isEmpty()) {
		logInfo("δѡ���κ��ļ���");
		return;
	}
	current = QString("%1/%2").arg(current, sel);
	std::vector<cv::Mat> matrixs = helper.readImageIntoMatrixVectorWithGDAL(current,3);
	//��ÿһ�����ι�һ��
	for (size_t i = 0; i < matrixs.size(); i++)
		matrixs[i] = helper.convert28UMatrix(matrixs[i]);

	cv::Mat result;
	cv::merge(matrixs, result);
	
	savePath = QString("%1.%2").arg(savePath,ext);
	if (cv::imwrite(savePath.toStdString(), result))
		logInfo("OK");
	else
		logInfo("Error");

	//�жϲ���

}

void ToolsFormaterImage::on_pbCancle_clicked()
{
}
