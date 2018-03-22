// opencv.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

#include "opencv2/opencv.hpp"
#include "Probabilities.hpp"

using namespace androprob;
using namespace cv;
using namespace std;

const int WIDTH = 1980;
const int HEIGHT = 900;
const float RANGE = 10;
const int SAMPELS = 1000;
const float START_Y = HEIGHT - HEIGHT / 30;
const int POINTS_PER_DISTRIBUTION = 100;

const float u1 = 0.5; const float s1 = 2.0f;
const float u2 = 7; const float s2 = 1.0f;
const float u3 =-6; const float s3 = 0.7f;

std::string float_to_string(const float value)
{
	static char buffer[128];
	sprintf_s(buffer, 128, "%.1f", value);
	return std::string(buffer);
}


void PlotProb()
{
	std::vector<float> points;
	Mat img = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

	const int START_X = WIDTH / 30;
	const float N = 30;


	//draw function
	double prevY = Probabilities::getProb_Of_N_or_More(0, N, 3);
	cv::Point p1(cv::Point(START_X , START_Y - prevY * (START_Y)));
	cv::Point py1(START_X, START_Y);

	cv::Point p2;
	cv::Point py2;
	Scalar color = Scalar(5, 25, 255);
	Scalar colorDT = Scalar(200, 55, 25);
	for (int n = 1; n < N; n++)
	{
		double y = Probabilities::getProb_Of_N_or_More(n, N, 3);
		double dy =  prevY - y;

		p2 = cv::Point(START_X + (float)n / N * (WIDTH - START_X), START_Y - y * (START_Y));
		py2 = cv::Point(START_X + (float)(n-1) / N * (WIDTH - START_X), START_Y - dy * (START_Y));
		line(img, p1, p2, color, 3, 8, 0);
		line(img, py1, py2, colorDT, 3, 8, 0);
		p1 = p2;
		py1 = py2;
		prevY = y;
	}



	//draw base lines
	line(img, cv::Point(0, START_Y), cv::Point(WIDTH, START_Y), Scalar(0, 255, 0), 2, 8, 0);
	line(img, cv::Point(START_X, 0), cv::Point(START_X, HEIGHT), Scalar(0, 255, 0), 1, 8, 0);


	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 0.31;
	cv::Size size = getTextSize(float_to_string(1.0f), fontFace, fontScale, 1, nullptr);

	//draw axis scale
	for (int n = 0; n < N; n++)
	{
		float x = START_X + (float)n / N * (WIDTH - START_X);
		line(img, cv::Point(x, 0), cv::Point(x, HEIGHT), Scalar(255, 255, 255), 1,8, 0);
		cv::Point sampleLoc = cv::Point(x, START_Y + 2 * size.height);
		putText(img, float_to_string(n), sampleLoc, fontFace, fontScale, Scalar(0, 255, 255));
	}
	for (int n = 0; n < 100; n++)
	{
		float y = START_Y - (float)n / 100 * (START_Y);
		if (n % 5 == 0)
		{
			line(img, cv::Point(0, y), cv::Point(WIDTH, y), Scalar(255, 255, 255), 1, 8, 0);
		}

		cv::Point sampleLoc = cv::Point(START_X - 2 * size.width, y);
		putText(img, float_to_string(n), sampleLoc, fontFace, fontScale, Scalar(0, 255, 255));
	}




	imshow("test", img);
	waitKey();

}


int main(int argc, char *argv[])
{
	PlotProb();
	return 0;
}

