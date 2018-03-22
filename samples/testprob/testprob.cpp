// opencv.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <functional>

#include "opencv2/opencv.hpp"
#include "Probabilities.hpp"
#include <Utils.hpp>

using namespace androprob;
using namespace cv;
using namespace std;


void PlotProb()
{
	std::vector<float> points;
	const int WIDTH = 1980;
	const int HEIGHT = 1080;
	const float START_Y = HEIGHT - HEIGHT / 30;
	const int START_X = WIDTH / 30;
	int N = 30;


	Mat img = Mat(HEIGHT, WIDTH, CV_8UC3, cv::Scalar(255, 255, 255));
	
	for (int i = 0; i < 100; i++)
	{
		N += 1;

		img = Mat(HEIGHT, WIDTH, CV_8UC3, cv::Scalar(255, 255, 255));


		//draw function
		double prevY = Probabilities::getProb_Of_N_or_More(0, N, 3);
		cv::Point p1(cv::Point(START_X, START_Y - prevY * (START_Y)));
		cv::Point py1(START_X, START_Y);

		cv::Point p2;
		cv::Point py2;
		Scalar color = Scalar(5, 25, 255);
		Scalar colorDT = Scalar(200, 55, 25);
		for (int n = 1; n < N; n++)
		{
			double y = Probabilities::getProb_Of_N_or_More(n, N, 3);
			double dy = prevY - y;

			p2 = cv::Point(START_X + (float)n / N * (WIDTH - START_X), START_Y - y * (START_Y));
			py2 = cv::Point(START_X + (float)(n - 1) / N * (WIDTH - START_X), START_Y - dy * (START_Y));
			line(img, p1, p2, color, 3, 8, 0);
			line(img, py1, py2, colorDT, 3, 8, 0);
			p1 = p2;
			py1 = py2;
			prevY = y;
		}



		androcv::DrawGraph(img, N, 100, cv::Point(START_X, START_Y), cv::Point(WIDTH, HEIGHT));


		imshow("test", img);
		if (waitKey() == 27)
			break;
	}

}


int main(int argc, char *argv[])
{
	PlotProb();
	return 0;
}

