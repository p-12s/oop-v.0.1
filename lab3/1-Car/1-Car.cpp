#include "stdafx.h"
#include "ControlPanel.h"
#include "Car.h"

using namespace std;

void main(int argc, char* argv[])
{
	CCar car;
	CControlPanel controlPanel(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!controlPanel.HandleCommand())
		{
			cout << "Unknown command" << endl;
		}
	}
}