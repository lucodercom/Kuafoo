#include "ImageHelper.h"
#include <qDebug>

std::vector<cv::Mat> ImageHelper::readImageIntoMatrixVectorWithGDAL(QString image)
{
	std::vector<cv::Mat> matrix;
	//GDAL读取所有的波段
	//GDAL按照顺序保存所有的波段
	GDALAllRegister();//注册、读取图像
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//使之支持中文路径
	GDALDataset* poDataset = nullptr;
	poDataset = (GDALDataset*)GDALOpen(image.toStdString().c_str(), GA_ReadOnly);
	if (poDataset == nullptr)
	{
		GDALDestroyDriverManager();
	}

	int bandPointer = 0;
	for (int i = 1; i <= poDataset->GetRasterCount(); i++)
	{
		int bandList = { 1 };
		cv::Mat band0 = cv::Mat(poDataset->GetRasterYSize(), poDataset->GetRasterXSize(), gdalType2opencvType(poDataset->GetRasterBand(i)->GetRasterDataType()), cv::Scalar::all(0));
		poDataset->RasterIO(GF_Read, 0, 0, band0.cols, band0.rows, band0.data, band0.cols, band0.rows, opencvType2GdalType(band0.type()), 1, &bandList, 0, 0, 0);

		matrix.push_back(band0);
	}

	//关闭GDAL库相关驱动和释放内存
	GDALClose(poDataset);
	return matrix;
}

void ImageHelper::saveImageFromMatrixVectorWithGDAL(QString image, std::vector<cv::Mat> matrix)
{
	
}

int ImageHelper::gdalType2opencvType(GDALDataType gdalType) {
	switch (gdalType)
	{
	case GDALDataType::GDT_Byte:return CV_8UC1;
	case GDALDataType::GDT_UInt16: return CV_16UC1;
	case GDALDataType::GDT_Int16: return CV_16SC1;
	case GDALDataType::GDT_UInt32: return CV_32SC1;
	case GDALDataType::GDT_Int32: return CV_32SC1;
	case GDALDataType::GDT_Float32: return CV_32FC1;
	case GDALDataType::GDT_Float64: return CV_64FC1;
	default:
		return CV_8UC1;
	}
}
GDALDataType ImageHelper::opencvType2GdalType(int opencv) {
	switch (opencv)
	{
	case CV_8UC1:  return GDT_Byte;
	case CV_16UC1: return  GDT_UInt16;
	case CV_16SC1: return  GDT_Int16;
	case CV_32SC1: return  GDT_UInt32;
	case CV_32FC1: return  GDT_Float32;
	case CV_32FC2: return  GDT_Float64;
	default:
		return GDT_Byte;
	}
}

QImage ImageHelper::cvMatToQImage(const cv::Mat & mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}