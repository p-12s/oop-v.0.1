#pragma once
#include "IShape.h"

class CShapesCreator
{
public:
	CShapesCreator();
	~CShapesCreator() = default;
	std::shared_ptr<IShape> CreateShapesFromString(const std::string& commandLine) const;

private:	
	std::shared_ptr<IShape> CreateLineSegment(std::istream& strm) const;
	std::shared_ptr<IShape> CreateRectangle(std::istream& strm) const;
	std::shared_ptr<IShape> CreateCircle(std::istream& strm) const;
	std::shared_ptr<IShape> CreateTriangle(std::istream& strm) const;
	
	typedef std::map<std::string, std::function<std::shared_ptr<IShape>(std::istream& args)>> ActionMap;
	const ActionMap m_actionMap;
};