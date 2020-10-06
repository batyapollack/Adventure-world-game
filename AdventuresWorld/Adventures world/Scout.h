//----------------------------------include------------------------------------------------
#pragma once
#include "Guard.h"
#include <list>
#include "Macros.h"
//--------------------------------class----------------------------------------------------
class Board;
//-----------------------------class Scout-------------------------------------------------
class Scout:public Guard
{
public:
	Scout(); //default Ctor of  Scout
	~Scout();//Dtor of Scout
	Scout(const sf::Vector2f& pos);//C'TOR OBJECT THAT UPDATE THE POSITION
	void moveEnemy() final {}//moveEnemy
	void moveScout(const std::vector <std::vector<bool>>& m_boardGraph,const sf::Vector2i posP);//moveScout
	void changeMove()final{}//changeMove
	void clearPath();//clearPath

	private:
		//--------------------------------private functions-----------------------------------
		void makeNewPath(const std::vector <std::vector<bool>>& m_boardGraph, const sf::Vector2i posP);
		void changeMoveVector(DIRECTION dircetion);
		//---------------------------------data members---------------------------------------
		static bool m_registerit;//m_registerit
		std::list<DIRECTION> path; // path to move
		DIRECTION m_moveDirection; // the moveDiraction
		sf::Vector2f m_startPoint; // the start point on the board
		sf::Vector2f m_prevPosition; // prevPosition of the character
		sf::Vector2f m_moveTo; // where user to move
};

