#pragma once
#include "IShape.h"

class CCreatorOfShapes
{
public:
	CCreatorOfShapes();
	~CCreatorOfShapes() = default;
	std::shared_ptr<IShape> CreateShapesFromString(const std::string& commandLine) const;

private:
	
	std::shared_ptr<IShape> CreateLineSegment(std::istringstream& strm) const;
	std::shared_ptr<IShape> CreateRectangle(std::istringstream& strm) const;
	std::shared_ptr<IShape> CreateCircle(std::istringstream& strm) const;
	std::shared_ptr<IShape> CreateTriangle(std::istringstream& strm) const;
	
	typedef std::map<std::string, std::function<std::shared_ptr<IShape>(std::istringstream& args)>> ActionMap;
	// прокатит ли здесь вместо istringstream - istream? 
	const ActionMap m_actionMap;
};