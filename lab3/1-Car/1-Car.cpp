#include "stdafx.h"
#include "ControlPanel.h"
#include "Car.h"

using namespace std;

void main()
{
	CCar car;
	CControlPanel controlPanel(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!controlPanel.HandleCommand())
			car.m_lastError;
		cout << endl;
	}
}