#pragma once

namespace androprob
{
	class Gaussian
	{
	public:
		Gaussian();
		Gaussian(float mean, float sigma);
		void setMean(float mean);
		void setSigma(float sigma);

		float getMean() const { return _mean; }
		float getSigma() const { return _sigma; }
		float pdf(float x) const;
	private:
		float _sigma;
		float _sigmaSq;
		float _sigmaInv;

		float _mean;
	};
}
