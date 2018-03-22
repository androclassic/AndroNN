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
#include "Gaussian.hpp"
#include "ExpectationMaximization.hpp"
#include "Utils.hpp"

using namespace cv;
using namespace std;
using namespace androprob;

const int SAMPELS = 1000;
const float RANGE = 10;


std::string float_to_string(const float value)
{
	static char buffer[128];
	sprintf_s(buffer, 128, "%.1f", value);
	return std::string(buffer);
}

void DrawGaussian(Mat img, const Gaussian& g, Point origin, Point size, Scalar color = Scalar(255,255,255))
{
	cv:Point p1(origin.x, origin.x +  size.y);
	cv::Point p2;
	for (int n = 0; n < SAMPELS; n++)
	{
		float  x = n * 2 * RANGE / SAMPELS - RANGE;
		float p = g.pdf(x);

		p2 = cv::Point(origin.x + (float)n / SAMPELS * size.x, origin.y - size.y * p);
		line(img, p1, p2, color, 2, 8, 0);
		p1 = p2;
	}
}


void TestEM()
{

	const int WIDTH = 1980;
	const int HEIGHT = 900;
	const float START_Y = HEIGHT - HEIGHT / 30;
	const int POINTS_PER_DISTRIBUTION = 100;

	const float u1 = 0.5; const float s1 = 2.0f;
	const float u2 = 7; const float s2 = 1.0f;
	const float u3 = -6; const float s3 = 0.7f;


	std::random_device rd{};
	std::mt19937 gen{ rd() };

	std::vector<float> points;
	Mat img = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

	Gaussian g1(u1, s1);	std::normal_distribution<> d1{ u1, s1 };
	Gaussian g2(u2, s2);	std::normal_distribution<> d2{ u2, s2 };
	Gaussian g3(u3, s3); std::normal_distribution<> d3{ u3, s3 };

	//generate points 
	for (int i = 0; i < POINTS_PER_DISTRIBUTION; i++)
	{
		points.push_back(d1(gen));
		points.push_back(d2(gen));
		points.push_back(d3(gen));
	}

	//text EM

	androprob::EM em(3);
	em.Train(points);

	cv::Point origin(WIDTH /40, START_Y);
	cv::Point size(WIDTH, HEIGHT);
	bool exit = false;
	int control = 0;
	while (!exit)
	{
		img = Mat(HEIGHT, WIDTH, CV_8UC3, cv::Scalar(255, 255, 255));

		//draw gaussians
		DrawGaussian(img, g1, origin, size,Scalar(0, 255, 255));
		DrawGaussian(img, g2, origin, size,Scalar(255, 0, 255));
		DrawGaussian(img, g3, origin, size,Scalar(0, 0, 255));

		//draw points
		float radius = 6.0f;
		for (auto p : points)
		{
			float x = (p + RANGE) / (2 * RANGE) * size.x;
			circle(img, cv::Point(origin.x + x, origin.y- radius), radius, Scalar(255, 0, 255), 1);
		}

		const std::vector<Gaussian>& computedDistr = em.getGaussians();
		for (auto distr : computedDistr)
		{
			DrawGaussian(img, distr, origin, size, Scalar(255, 0, 30));
		}

		androcv::DrawGraph(img, RANGE, 10, origin, size);
		control = androcv::Controls(origin, size);

		if (control == 't')
		{
			em.Train(points);
		}

		exit = control == 27;
		imshow("test", img);

	}

}

int main(int argc, char *argv[])
{
	TestEM();

	return 0;
}

