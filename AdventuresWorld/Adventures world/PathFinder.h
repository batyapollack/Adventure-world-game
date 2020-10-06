//---------------------------------include---------------------------------------
#pragma once
#include "Macros.h"
#include <vector>		// mase hold in vector
#include <array>		// array for easy pass updown left rigth
#include <queue>		// to use bfs like algortiom
#include <list>			// to return the path
//--------------------------------------------------------------------------------
//use to find the shortes path in maze from start to destination
//--------------------struct GraphNode--------------------------------------------
struct GraphNode
{
	sf::Vector2i m_previous; // previous cordes
	DIRECTION m_prevDirec; // prev direc
	bool m_pass; // if node did pass
	GraphNode() : m_previous(-1, -1), m_prevDirec(NONE_D), m_pass(false) {}; //Ctor of  GraphNode
};
//-----------------class PathFinder -----------------------------------------------
class PathFinder {
	// find the shortes path for start to destination
	// input: maze  the maze to move one
	// start : start point, destination: to where go from maze
	// if there isn't path return empty list
public:
	static std::list<DIRECTION> searchPath(const std::vector<std::vector<bool>> &maze
		, const sf::Vector2i &start, const sf::Vector2i &destination);
};

