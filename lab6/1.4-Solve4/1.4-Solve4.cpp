#include "stdafx.h"
#include "Solve4.h"

using namespace std;

void PrintRoots(const EquationRoot4& roots)
{
	cout << "Equation roots are: ";
	for (size_t i = 0; i < roots.numRoots; ++i)
	{
		cout << roots.roots[i] << "; ";
	}
	cout << endl;
}

int main()
{
	cout << "Enter 5 coefficients of the equation of 4 degrees:" << endl;
	double a, b, c, d, e;
	
	while (!cin.eof())
	{
		try
		{
			if ((cin >> a) && (cin >> b) && (cin >> c) && (cin >> d) && (cin >> e))
			{
				PrintRoots(Solve4(a, b, c, d, e));
			}
			else
			{
				cin.clear();	// reset the status flag of the stream
				cin.ignore(cin.rdbuf()->in_avail());	// turn to the buffer, ask how many characters it stores and ignore them
				cout << "Odds are entered incorrectly, enter 5 numbers" << endl;				
			}
		}
		catch (const exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
	return 0;
}
