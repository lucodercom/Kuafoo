#include <QString>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <gdal_priv.h>

class ImageHelper
{
public:
	std::vector<cv::Mat> readImageIntoMatrixVectorWithGDAL(QString image);
	void saveImageFromMatrixVectorWithGDAL(QString image, std::vector<cv::Mat> matrix);
	QImage cvMatToQImage(const cv::Mat & mat);
	GDALDataType opencvType2GdalType(int opencv);
	int gdalType2opencvType(GDALDataType gdalType);
};

