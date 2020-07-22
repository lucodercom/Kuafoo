#pragma once
#include <opencv2/opencv.hpp>
#include <QString>
class ToolsFormaterImageController
{
public:
	bool saveAsTiff(QString path,std::vector<cv::Mat> matrix);
	bool saveAsOthers(QString path,std::vector<cv::Mat> matrix);
};

