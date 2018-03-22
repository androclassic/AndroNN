#include "ExpectationMaximization.hpp"
#include <iostream>
#include <random>


namespace androprob
{

	EM::EM(int nClusters, int max_iterations)
		: _priors(nClusters, (innerType)1.0 / nClusters)
	{
		_max_iterations - max_iterations;
		_gaussians.resize(nClusters);
		_posteriors.resize(nClusters);
		_init = false;
	}

	//set priors equal and randomly pick means from data 
	void EM::InitMeans(const std::vector<float>& points)
	{
		int clustersNb = _gaussians.size();
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, points.size() - 1); // define the range

		for (int k = 0; k < clustersNb; k++)
		{
			_priors[k] = 1.0 / clustersNb;
			_gaussians[k].setMean(points[distr(eng)]);
		}


	}
	void EM::Train(const std::vector<float>& points, bool forceInit)
	{
		int clustersNb = _gaussians.size();

		if (!_init || forceInit)
		{
			_init = true;
			InitMeans(points);
		}

		//

		for (int i = 0; i < _posteriors.size(); i++)
			_posteriors[i].clear();

		//e-step
		for (int i = 0; i < points.size(); i++)
		{
			innerType x = points[i];

			//compute posteriors
			innerType posterior_denominator = 0;
			for (int k = 0; k < clustersNb; k++)
			{
				innerType posterior_numerator = _gaussians[k].pdf(x) * _priors[k];
				posterior_denominator += posterior_numerator;
				_posteriors[k].push_back(posterior_numerator);
			}
			for (int k = 0; k < clustersNb; k++)
			{
				_posteriors[k][i] /= posterior_denominator;
			}
		}

		//m-step
		for (int k = 0; k < clustersNb; k++)
		{
			innerType mean = 0;
			innerType sigma = 0;
			innerType posterior_sum = 0;

			//compute means
			for (int i = 0; i < points.size(); i++)
			{
				posterior_sum += _posteriors[k][i];
				mean += _posteriors[k][i] * points[i];
			}
			mean /= posterior_sum;

			//compute sigma
			for (int i = 0; i < points.size(); i++)
			{
				sigma += _posteriors[k][i] * ((points[i] - mean) * (points[i] - mean));
			}
			sigma /= posterior_sum;

			//estimate priors
			_priors[k] = posterior_sum / points.size();


			_gaussians[k].setMean(mean);
			_gaussians[k].setSigma(sqrt(sigma));
		}






	}
}


