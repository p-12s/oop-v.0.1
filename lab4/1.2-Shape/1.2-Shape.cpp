#include "stdafx.h"
#include "Point.h"
#include "LineSegment.h"

using namespace std;

int main()
{
	CPoint startPoint = CPoint(0.0, 0.0);
	CPoint endPoint = CPoint(-10.0, -10.0);
	string color = "ff0000";
	CLineSegment lineSegment = CLineSegment(startPoint, endPoint, color);

	cout << lineSegment.ToString() << endl;

    return 0;
}

