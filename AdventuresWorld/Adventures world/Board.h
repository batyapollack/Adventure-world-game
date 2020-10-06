//---------------------------include--------------------------------------------
#pragma once
#include <vector>
#include<string>
#include<memory>
#include "NoneAlive.h"
#include <fstream>
#include <iostream>
#include "Macros.h"
#include <SFML/Graphics.hpp>
#include "Guard.h"
//------------------------class-------------------------------------------------
class Key;
class Player;
class Snow;
//----------------------class Board---------------------------------------------
class Board
{
public:
	Board(unsigned int currLevel,Player& player,std::vector<std::unique_ptr <Enemy>>&enemies,
		std::vector<std::unique_ptr <Key>> &keys, std::vector<std::unique_ptr <Snow>> &snows,
		std::vector<std::unique_ptr<NoneAlive>>& m_static_vec,
		std::vector <std::vector<bool>> &boardGraph); //Ctor of Board
	~Board(){} //Dtor of Board
	bool insertToMatrix(unsigned int & currLevel,Player& player, std::vector<std::unique_ptr <Enemy>>&enemies,
		std::vector<std::unique_ptr <Key>> &keys, std::vector<std::unique_ptr <Snow>> &snows, 
		std::vector<std::unique_ptr<NoneAlive>>& m_static_vec,
		std::vector <std::vector<bool>> &boardGraph); //insertToMatrix
	const sf::Vector2i& getPosPlayer()const { return m_pos_player; }  //getPosPlayer

private:
	//-----------------------private function------------------------------------
	void fillGraphObstacle(sf::Vector2i pos, int row, int col); //fillGraphObstacle
	void rangeDim(const  int& row,const int & col)const;
	void readFromFile(std::ifstream & inputFile, int dimY, std::string & currline);//readFromFile
	void checkFile(std::ifstream & inputFile, int dimY, std::string & currline);//checkFile
	void openFile(std::ifstream &inputFile, int level);//openFile
	void randKeyNum(std::vector<std::unique_ptr <Key>> &keys);//randKeyNum
	void resetGraphTrue(int dimX, int dimY);//resetGraphTrue
	bool isEnemyType(const char& type)const ;//isEnemyType
	bool isStaticType(const char & type)const;//isStaticType
	bool isItemsType(const char & type)const; //isItemsType
	void keyAlloc(Creature* creature, std::vector<std::unique_ptr <Key>> &keys)const;//keyAlloc
	void snowAlloc(Creature* creature, std::vector<std::unique_ptr <Snow>> &snows)const;//snowAlloc
	void enemyAlloc(Creature* creature, std::vector<std::unique_ptr <Enemy>> &enemies)const;//enemyAlloc
	void staticAlloc(Creature* creature, std::vector<std::unique_ptr <NoneAlive>> &m_static_vec)const;//staticAlloc
	void isCastle(Creature* creature, int row, int col);//isCastle
	void isHomeEnemy(Creature* creature, int row, int col);//isHomeEnemy
	void isTower(Creature* creature, int row, int col);//isTower
	CREATURE_T getCreatureEnumFromChar(const char&) const;//getCreatureEnumFromChar
	//---------------------data members-------------------------------------------
	sf::Vector2f Tilepos;//Tilepos
	std::vector <std::vector<bool>>& m_boardGraph;//m_boardGraph
	sf::Vector2i m_pos_player;//m_pos_player
};

