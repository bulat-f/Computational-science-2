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
	KFU::Vector<double> true_solution = S.solve();
	KFU::Vector<double> solution = S.true_solution();

	KFU::Vector<double> jacobi = S.jacobi(epsilon);
	KFU::Vector<double> seidel = S.seidel(epsilon);
	KFU::Vector<double> relaxation = S.relaxation(epsilon, omega);

	// cout << true_solution - solution << endl;
	cout << (solution - jacobi).abs_max() << endl << S.get_jacobi_counter() << endl;
	cout << (solution - seidel).abs_max() << endl << S.get_seidel_counter() << endl;
	cout << (solution - relaxation).abs_max() << endl << S.get_relaxation_counter() << endl;
	cout << (solution - true_solution).abs_max() << endl << S.get_relaxation_counter() << endl;
	return 0;
}
