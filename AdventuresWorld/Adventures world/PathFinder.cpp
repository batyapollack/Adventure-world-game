//-------------------------include---------------------------------------------
#include "PathFinder.h"
//--------------------------searchPath------------------------------------------
//function that  search the shortes path in maze from start to destination
std::list<DIRECTION> PathFinder::searchPath(const std::vector<std::vector<bool>>& maze, const sf::Vector2i & start, const sf::Vector2i & destination)
{
	std::vector<std::vector<GraphNode>> egdes; // to save every node prev
	egdes.resize(maze.size()); // maze egeds array all set by defaule consractor
	for (size_t i = 0; i < egdes.size(); i++)
		egdes[i].resize(maze[0].size());	// garph GraphNode
											// to move up down left right
	static const std::array<sf::Vector2i, 4> moves
		= { sf::Vector2i(-1, 0), // up
			sf::Vector2i(1, 0), // down
			sf::Vector2i(0, -1), // rigt
			sf::Vector2i(0, 1) }; // left

  // loop as long there item in the queune and destination didn't found
	std::queue<sf::Vector2i> nodeQueue; // make queue to maze

	nodeQueue.push(start); // enter start to the queune
	egdes[start.x][start.y].m_pass = true; // make start as pass
	while (!nodeQueue.empty() && !(egdes[destination.x][destination.y].m_pass))
	{
		sf::Vector2i currNode = nodeQueue.front(); // get item form the quecue
		nodeQueue.pop(); // remove from queue

		for (size_t i = 0; i < moves.size(); i++)
		{
			sf::Vector2i temp = moves[i] + currNode; // next node to mode

													 // case temp if out bound
			if (temp.x < 0 || temp.y < 0 ||
				temp.x >= static_cast<int>(egdes.size()) || temp.y >= static_cast<int>(egdes[0].size()))
				continue;
			// if there wall in the maze skip it
			// or some egede pass on this egede
			if (!maze[temp.x][temp.y] || egdes[temp.x][temp.y].m_pass)
				continue;

			else
			{
				nodeQueue.push(temp); // put node in the queue
				egdes[temp.x][temp.y].m_pass = true; // set it pass
				egdes[temp.x][temp.y].m_previous = currNode; // set it curr node
				switch (i) // set the prevDirection to the node
				{
				case 0:
					egdes[temp.x][temp.y].m_prevDirec = UP_D;
					break;
				case 1:
					egdes[temp.x][temp.y].m_prevDirec = DOWN_D;
					break;
				case 2:
					egdes[temp.x][temp.y].m_prevDirec = LEFT_D;
					break;
				case 3:
					egdes[temp.x][temp.y].m_prevDirec = RIGHT_D;
					break;
				default:
					break;
				}

			}
		}
	}

	std::list <DIRECTION> path; // the path
	if (!egdes[destination.x][destination.y].m_pass) // if there isn't path
		return path;								// return empty list
	sf::Vector2i currNode = destination; // move back for destion to start to 
	while (currNode != start) // move until start
	{
		path.push_front(egdes[currNode.x][currNode.y].m_prevDirec); // put direction on the list head
		currNode = sf::Vector2i(egdes[currNode.x][currNode.y].m_previous); // move to the next node
	}
	return path; // the shorter path from start to destination

}

