#pragma once
#include "IShape.h"

std::shared_ptr<IShape> CalculateLargestArea(const std::vector<std::shared_ptr<IShape>>& shapes);

std::shared_ptr<IShape> CalculateLeastPerimeter(const std::vector<std::shared_ptr<IShape>>& shapes);