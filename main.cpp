#include <iostream>
#include <fstream>
#include <getopt.h>
#include <cstdlib>
#include "linear_system.h"

using namespace std;

int main(int argc, char *argv[])
{
	int n = 10;
	double epsilon = 1e-4, omega = 1.5;

	const char *short_options = "neo";

	const struct option long_options[] = {
		{ "numbers", required_argument, NULL, 'n' },
		{ "epsilon", required_argument, NULL, 'e' },
		{ "omega", required_argument, NULL, 'o' },
		{ NULL, no_argument, NULL, 0 }
	};

	int result, option_index = 0;

	while ((result = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch (result)
		{
			case 'n':
				if (optarg != NULL) n = atoi(optarg);
				break;
			case 'e':
				if (optarg != NULL) epsilon = atof(optarg);
				break;
			case 'o':
				if (optarg != NULL) omega = atof(optarg);
				break;
		}
	}

	KFU::LinearSystem S(n - 1);

	cout << "True solution\n" << S.solve();
	cout << "Jacobi method\n" << S.jacobi(epsilon);
	cout << "Seidel method\n" << S.seidel(epsilon);
	cout << "Relaxation method\n" << S.relaxation(epsilon, omega);
	return 0;
}
