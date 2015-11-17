#include "helpers.h"

#include <cmath>

namespace helpers
{
	double h(int n)
	{
		return 1 / (double) (n - 1);
	}

	double u(double x)
	{
		return pow(x, 3) * pow((1 - x), 4);
	}

	double p(double x)
	{
		return 1 + pow(x, 3);
	}

	double g(double x)
	{
		return 1 + x;
	}

	double f(int i, int n)
	{
		return f_helper(i*h(n));
	}

	double f_helper(double x)
	{
		return -3 * pow(x-1, 3) * pow(x, 2) * (7 * x - 3) -
			6 * (1 + pow(x, 3)) * pow(x - 1, 2) * x * (7 * pow(x, 2) - 6 * x + 1) +
			(1 + x) * pow(x, 3) * pow(x - 1, 4);
	}
}
