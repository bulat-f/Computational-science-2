#include <iostream>
#include <fstream>
#include "linear_system.h"

using namespace std;

int main()
{
	ifstream in("input.in");
	KFU::LinearSystem S(11);
	cout << S;
	return 0;
}
