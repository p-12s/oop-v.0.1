#include "stdafx.h"
#include "CalculatingShapes.h"

using namespace std;

shared_ptr<IShape> CalculateLargestArea(const vector<shared_ptr<IShape>>& shapes)
{
	if (shapes.empty())
		return nullptr;

	auto shape = max_element(shapes.begin(), shapes.end(),
		[](auto&& a, auto&& b)
	{
		return a->GetArea() < b->GetArea();
	});

	return *shape;
}

shared_ptr<IShape> CalculateLeastPerimeter(const vector<shared_ptr<IShape>>& shapes)
{
	if (shapes.empty())
		return nullptr;

	auto shape = min_element(shapes.begin(), shapes.end(),
		[](const shared_ptr<IShape>& a, const shared_ptr<IShape>& b)
	{
		return a->GetPerimeter() < b->GetPerimeter();
	});

	return *shape;
}