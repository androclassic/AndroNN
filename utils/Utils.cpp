#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <functional>

#include "Utils.hpp"

using namespace cv;
using namespace std;
namespace androcv
{


	std::string float_to_string(const float value)
	{
		static char buffer[128];
		sprintf_s(buffer, 128, "%.1f", value);
		return std::string(buffer);
	}

	void DrawGraph(Mat& img, int x_Scale, int y_Scale, cv::Point origin, cv::Point graph_size, int line_space_x, int line_space_y)
	{
		int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
		double fontScale = 0.31;
		cv::Size size = getTextSize(float_to_string(1.0f), fontFace, fontScale, 1, nullptr);

		//draw x axis scale 
		for (int n = 0; n < x_Scale; n++)
		{
			float x_p = origin.x + static_cast<float>(n) / x_Scale * (graph_size.x);
			float x_n = origin.x - static_cast<float>(n) / x_Scale * (graph_size.x);

			if (n%line_space_x == 0)
			{
				//draw x line scale pos
				line(img, cv::Point(x_p, origin.y - graph_size.y), cv::Point(x_p, origin.y + graph_size.y), Scalar(0, 0, 0), 1, 8, 0);
				//draw x line scale neg
				line(img, cv::Point(x_n, origin.y - graph_size.y), cv::Point(x_n, origin.y + graph_size.y), Scalar(0, 0, 0), 1, 8, 0);
			}

			//draw x anotation scale pos
			cv::Point sampleLoc = cv::Point(x_p, origin.y + 2 * size.height);
			putText(img, float_to_string(n), sampleLoc, fontFace, fontScale, Scalar(255, 0, 0));
			//draw x anotation scale neg
			cv::Point sampleLocNeg = cv::Point(x_n, origin.y + 2 * size.height);
			putText(img, float_to_string(n), sampleLocNeg, fontFace, fontScale, Scalar(255, 0, 0));
		}


		//draw  y axis scale
		for (int n = 0; n < y_Scale; n++)
		{
			float y_p = origin.y - static_cast<float>(n) / y_Scale * (graph_size.y);
			float y_n = origin.y + static_cast<float>(n) / y_Scale * (graph_size.y);

			if (n%line_space_y == 0)
			{
				//draw y line scale pos
				line(img, cv::Point(origin.x - graph_size.x, y_p), cv::Point(origin.x + graph_size.x, y_p), Scalar(0, 0, 0), 1, 8, 0);
				//draw y line scale neg
				line(img, cv::Point(origin.x - graph_size.x, y_n), cv::Point(origin.x + graph_size.x, y_n), Scalar(0, 0, 0), 1, 8, 0);
			}

			//draw y anotation scale pos
			cv::Point sampleLoc = cv::Point(origin.x - 2 * size.width, y_p);
			putText(img, float_to_string(n), sampleLoc, fontFace, fontScale, Scalar(255, 0, 0));


			//draw y anotation scale neg
			cv::Point sampleLocN = cv::Point(origin.x - 2 * size.width, y_n);
			putText(img, float_to_string(-n), sampleLocN, fontFace, fontScale, Scalar(255, 0, 0));
		}

		//draw base lines
		line(img, cv::Point(origin.x -graph_size.x, origin.y), cv::Point(origin.x + graph_size.x, origin.y), Scalar(0, 255, 0), 2, 8, 0);
		line(img, cv::Point(origin.x, origin.y - graph_size.y), cv::Point(origin.x, origin.y  + graph_size.y), Scalar(0, 255, 0), 2, 8, 0);

	}



	int Controls(Point& origin, Point& size)
	{
		const int move_factor = 3;
		const float zoom_factor = 1.25;
		int c = waitKey();
		switch (c)
		{
			case 'Q':
			case 'q':
				size.y *= zoom_factor;
				size.x *= zoom_factor;
				break;
			case 'E':
			case 'e':
				size.y /= zoom_factor;
				size.x /= zoom_factor;
				break;

			case 2490368: // up arrow
				origin.y -= move_factor;
				break;
			case 2424832:  // right arrow 
				origin.x -= move_factor;
				break;

			case 2621440: //down arrow
				origin.y += move_factor;
				break;

			case 2555904: // left arrow
				origin.x += move_factor;
				break;
		}

		return c;
	}
	

}