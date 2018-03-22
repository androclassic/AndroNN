#include "Probabilities.hpp"
#include <math.h>
#include<iostream>

namespace androprob
{

	double Probabilities::combinations(unsigned int n, unsigned k)
	{
		if (k == 0)
			return 1;

		return (n * combinations(n - 1, k - 1)) / k;
	}



	double  Probabilities::getProb_Of_N_or_More(int n, int N, int k)
	{
		double res = 1.0; // comb(total, total) * 1

		double total_outcomes = pow(k, N);
		for (int i = n; i < N; i++)
		{
			// n choose i * pow(k-1, n-i))

			res += combinations(N, i) * std::pow(k - 1, N - i);
		}
		res /= total_outcomes;

		return res;
	}
}