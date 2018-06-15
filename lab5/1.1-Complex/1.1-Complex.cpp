#include "stdafx.h"
#include "Complex.h"

using namespace std;

int main()
{
	double expectedRe = 1.0;
	double expectedIm = -2.0;
	CComplex complex1(expectedRe, expectedIm);


	cout << complex1 << endl;
    return 0;
}

