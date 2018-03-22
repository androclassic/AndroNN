#pragma once
#include "Gaussian.hpp"
#include <vector>
namespace androprob
{

	class EM
	{
		typedef double innerType;

	public:
		EM(int nClusters, int max_iterations = 100);
		void Train(const std::vector<float>& points, bool forceInit = false);

		const std::vector<Gaussian>& getGaussians() const { return _gaussians; }
	private:
		void InitMeans(const std::vector<float>& points);
		bool  _init;

		int _max_iterations;
		std::vector<Gaussian> _gaussians;
		std::vector<innerType> _priors;
		std::vector<std::vector<innerType>> _posteriors;

	};

}