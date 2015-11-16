#include <iostream>
#include <fstream>
#include "linear_system.h"

using namespace std;

int main()
{
	ifstream in("input.in");
	KFU::LinearSystem S(3, 3);
	in >> S;
	cout << S.solve2();
	cout << S.solve();
	return 0;
}
