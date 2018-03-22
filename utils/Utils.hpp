#pragma once

#include "opencv2/opencv.hpp"

namespace androcv
{
	extern void DrawGraph(cv::Mat& img, int x_Scale, int y_Scale, cv::Point origin, cv::Point graph_size, int line_space_x = 1, int line_space_y = 1);
	extern 	int Controls(cv::Point& origin, cv::Point& size);

	class MouseControl
	{
	public:
		static void CallBackFunc(int event, int x, int y, int flags, void* userdata);

		static const cv::Point& getPosition() { return mouse_pos; }
		static const cv::Point& getMove() { return mouse_move; }
		static bool isLBPressed() { return left_buton_pressed; }

	private:
		static bool left_buton_pressed;
		static cv::Point mouse_pos;
		static cv::Point mouse_move;


	};

}

