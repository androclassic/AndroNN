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



void DrawFunction(Mat& img, int N, int x_Scale, int y_Scale, cv::Point origin, cv::Point graph_size)
{
	double prevY = Probabilities::getProb_Of_N_or_More(0, N, 3);
	cv::Point p1(cv::Point(origin.x, origin.y - prevY * (graph_size.y)));
	cv::Point py1 = origin;

	cv::Point p2;
	cv::Point py2;
	Scalar color = Scalar(5, 25, 255);
	Scalar colorDT = Scalar(200, 55, 25);
	for (int n = 1; n < N; n++)
	{
		double y = Probabilities::getProb_Of_N_or_More(n, N, 3);
		double dy = prevY - y;

		p2 = cv::Point(origin.x + (float)n / N * (graph_size.x), origin.y - y * (graph_size.y));
		py2 = cv::Point(origin.x + (float)(n - 1) / N * (graph_size.x), origin.y - dy * (graph_size.y));
		line(img, p1, p2, color, 3, 8, 0);
		line(img, py1, py2, colorDT, 3, 8, 0);
		p1 = p2;
		py1 = py2;
		prevY = y;
	}
}


void PlotProb()
{
	std::vector<float> points;
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	const float START_Y = HEIGHT - HEIGHT / 30;
	const int START_X = WIDTH / 30;
	int N = 30;


	//Create a window
	namedWindow("ImageDisplay", 1);
	//set the callback function for any mouse event
	setMouseCallback("ImageDisplay", androcv::MouseControl::CallBackFunc, NULL);


	Mat img = Mat(HEIGHT, WIDTH, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Point origin(START_X, START_Y);
	cv::Point size(WIDTH, HEIGHT);
	bool exit = false;
	while (!exit)
	{
		img = Mat(HEIGHT, WIDTH, CV_8UC3, cv::Scalar(255, 255, 255));

		//draw function
		DrawFunction(img, N, 1, 1, origin, size);
		androcv::DrawGraph(img, N, 100, origin, size);
		int c = androcv::Controls(origin, size);

		if(androcv::MouseControl::isLBPressed())
		{
			origin -= androcv::MouseControl::getMove();
		}

		if (c == 't') { N++; }
		else if(c =='r') { N--; }
		exit = c == 27;

		//show the image
		imshow("ImageDisplay", img);
	}

}


int main(int argc, char *argv[])
{
	PlotProb();
	return 0;
}

