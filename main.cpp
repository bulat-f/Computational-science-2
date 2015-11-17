#include <iostream>
#include <fstream>
#include "linear_system.h"

using namespace std;

int main()
{
	ifstream in("input.in");
	KFU::LinearSystem S(11);
	cout << "True solution\n" << S.solve();
	cout << "Jacobi method\n" << S.jacobi();
	cout << "Seidel method\n" << S.seidel();
	return 0;
}
