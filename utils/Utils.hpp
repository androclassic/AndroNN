#pragma once

#include "opencv2/opencv.hpp"

namespace androcv
{
	extern void DrawGraph(cv::Mat& img, int x_Scale, int y_Scale, cv::Point origin, cv::Point graph_size, int line_space_x = 1, int line_space_y = 1);
	extern 	int Controls(cv::Point& origin, cv::Point& size);
}

