#include "Gaussian.hpp"
#include <math.h>

#define INV_SQRT_OF_2PI  0.3989422804f
namespace androprob
{
	Gaussian::Gaussian()
	{
		setMean(1.0f);
		setSigma(1.0f);
	}

	Gaussian::Gaussian(float mean, float sigma)
	{
		setMean(mean);
		setSigma(sigma);
	}

	void Gaussian::setMean(float mean)
	{
		_mean = mean;
	}
	void Gaussian::setSigma(float sigma)
	{
		_sigma = sigma;
		_sigmaSq = sigma * sigma;
		_sigmaInv = 1.0f / sigma;

	}

	float Gaussian::pdf(float x) const
	{
		float dist = (x - _mean)*(x - _mean);
		return  INV_SQRT_OF_2PI * _sigmaInv * exp(-dist / (2.0f * _sigmaSq));
	}
}