#include "ImageHelper.h"
#include <qDebug>

std::vector<cv::Mat> ImageHelper::readImageIntoMatrixVectorWithGDAL(QString image, int bandSize)
{
	std::vector<cv::Mat> matrix;
	//GDAL读取所有的波段
	//GDAL按照顺序保存所有的波段
	GDALAllRegister();//注册、读取图像
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "YES");//使之支持中文路径
	GDALDataset* poDataset = nullptr;
	poDataset = (GDALDataset*)GDALOpen(image.toStdString().c_str(), GA_ReadOnly);
	if (poDataset == nullptr)
	{
		GDALDestroyDriverManager();
	}

	int bandPointer = 0;
	if (bandSize <= 0)
		bandSize = poDataset->GetRasterCount();
	
	int width = poDataset->GetRasterXSize();
	int height = poDataset->GetRasterYSize();
	int nband =  poDataset->GetRasterCount();
	bandSize = bandSize + 2 > nband ? nband : bandSize + 2;
	//float* p = new float[width * height];
	for (int i = 2; i <= bandSize; i++)
	{
		cv::Mat band0 = cv::Mat(height, width, gdalType2opencvType(poDataset->GetRasterBand(i)->GetRasterDataType()), cv::Scalar::all(0));

		poDataset->GetRasterBand(i)->RasterIO(
			GF_Read, 
			0, 0, height, width,
			band0.data, height, width,
			poDataset->GetRasterBand(i)->GetRasterDataType(),
			NULL,NULL);
		matrix.push_back(band0.clone());
		/*GDALRasterBand* bandData;
		bandData = poDataset->GetRasterBand(i);
		GDALDataType DataType = bandData->GetRasterDataType();
		bandData->RasterIO(GF_Read, 0, 0, width, height, p, width, height, DataType, 0, 0);
		cv::Mat HT(height, width, gdalType2opencvType(DataType), p);
		matrix.push_back(HT.clone());*/
	}

	/*cv::Mat band0 = cv::Mat(poDataset->GetRasterYSize(), poDataset->GetRasterXSize(), gdalType2opencvType(poDataset->GetRasterBand(1)->GetRasterDataType()), cv::Scalar::all(0));
	poDataset->RasterIO(GF_Read, 0, 0, band0.cols, band0.rows, band0.data, band0.cols, band0.rows, opencvType2GdalType(band0.type()), 1, 0, 0, 0, 0);
	matrix.push_back(band0.clone());

	cv::Mat band1 = cv::Mat(poDataset->GetRasterYSize(), poDataset->GetRasterXSize(), gdalType2opencvType(poDataset->GetRasterBand(2)->GetRasterDataType()), cv::Scalar::all(0));
	poDataset->RasterIO(GF_Read, 0, 0, band1.cols, band1.rows, band1.data, band1.cols, band1.rows, opencvType2GdalType(band1.type()), 2, 0, 0, 0, 0);
	matrix.push_back(band1.clone());

	cv::Mat band2 = cv::Mat(poDataset->GetRasterYSize(), poDataset->GetRasterXSize(), gdalType2opencvType(poDataset->GetRasterBand(3)->GetRasterDataType()), cv::Scalar::all(0));
	poDataset->RasterIO(GF_Read, 0, 0, band2.cols, band2.rows, band2.data, band2.cols, band2.rows, opencvType2GdalType(band2.type()), 3, 0, 0, 0, 0);
	matrix.push_back(band2.clone());*/

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
cv::Mat ImageHelper::convert28UMatrix(cv::Mat img)
{
	int width = img.cols;//图片宽度
	int height = img.rows;//图片高度
	cv::Mat dst = cv::Mat::zeros(height, width, CV_8UC1);//先生成空的目标图片
	double minv = 0.0, maxv = 0.0;
	double* minp = &minv;
	double* maxp = &maxv;
	minMaxIdx(img, minp, maxp);  //取得像素值最大值和最小值

	//用指针访问像素，速度更快
	ushort* p_img;
	uchar* p_dst;
	for (int i = 0; i < height; i++)
	{
		p_img = img.ptr<ushort>(i);//获取每行首地址
		p_dst = dst.ptr<uchar>(i);
		for (int j = 0; j < width; ++j)
			p_dst[j] = (p_img[j] - minv) / (maxv - minv) * 255;
	}
	return dst;
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

QImage ImageHelper::cvMatToQImage(const cv::Mat& mat)
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
		uchar* pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar* pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar* pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar* pSrc = (const uchar*)mat.data;
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