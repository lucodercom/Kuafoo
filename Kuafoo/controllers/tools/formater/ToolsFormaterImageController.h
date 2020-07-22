#pragma once
#include <opencv2/opencv.hpp>
class ToolsFormaterImageController
{
public:
	cv::Mat ConvertToTiff(std::vector<cv::Mat> matrix);
	cv::Mat ConvertToOthers(std::vector<cv::Mat> matrix);
};

