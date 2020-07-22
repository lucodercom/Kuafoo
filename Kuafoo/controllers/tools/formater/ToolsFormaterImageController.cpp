#include "ToolsFormaterImageController.h"

bool ToolsFormaterImageController::saveAsTiff(QString path, std::vector<cv::Mat> matrix)
{
	if (matrix.size <= 0)
		return;

	return true;
}

bool ToolsFormaterImageController::saveAsOthers(QString path, std::vector<cv::Mat> matrix)
{
	std::vector<cv::Mat> matrixs;

	if (matrix.size() <= 0)
		return false;

	int i = 0;
	while (i < 3 && !matrixs[i].empty())
		matrixs.push_back(matrix[i++].clone());

	cv::Mat output;
	cv::merge(matrixs, output);

	return cv::imwrite(path.toStdString(), output);
}
