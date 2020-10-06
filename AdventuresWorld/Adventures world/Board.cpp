//------------------------------include-------------------------------------------------------
#include "Board.h"
#include "Key.h"
#include "Factory.h"
#include "Player.h"
#include <random>
#include "WatchTower.h"
#include "Castle.h"
#include "RandMachine.h"
#include"Scout.h"
#include"Snow.h"
//--------------------------Board----------------------------------------------------------------
//Ctor that get data from Controller and call to function insertToMatrix
Board::Board(unsigned int currLevel, Player& player, std::vector<std::unique_ptr <Enemy>>&enemies,
	std::vector<std::unique_ptr <Key>>& keys, std::vector<std::unique_ptr <Snow>> &snows, std::vector<std::unique_ptr<NoneAlive>>& m_static_vec, std::vector <std::vector<bool>> &boardGraph)// VECTOR OF GAURDS
	:m_boardGraph(boardGraph)
{
	insertToMatrix(currLevel, player, enemies,keys,snows,m_static_vec, boardGraph);
}
//-------------------------insertToMatrix-------------------------------------------------------------
//function that passes the file and inserts the objects into the data structures corresponding to their type
bool Board::insertToMatrix( unsigned int & currLevel, Player& player, std::vector<std::unique_ptr <Enemy>>&enemies,
	std::vector<std::unique_ptr <Key>> &keys, std::vector<std::unique_ptr <Snow>> &snows, std::vector<std::unique_ptr<NoneAlive>>& m_static_vec, std::vector <std::vector<bool>> &boardGraph)
{
	try {
		std::ifstream inputFile; // to open file
		openFile(inputFile, currLevel); // open the file
		if (!inputFile.is_open())
		{
			currLevel--;
			return false; // fail to open file
		}
		int dimX, dimY; // the board dim
		std::string currline; // to get the curr line
		inputFile >> dimX >> dimY;

		rangeDim(dimX, dimY);
		getline(inputFile, currline); // eat space
		m_static_vec.resize(0);
		resetGraphTrue(dimX, dimY);
		for (int row = 0; row < dimX; row++)
		{
			checkFile(inputFile, dimY, currline);
			for (int col = 0; col < dimY; col++)
			{
				Tilepos = sf::Vector2f(col * SIZE_TILE, row * SIZE_TILE);

				auto staticObjType = getCreatureEnumFromChar(currline[col]);
				auto up = Factory::create(staticObjType);
				Creature* p = up.release();

				if (PLAYER_SIGN == currline[col])
				{
					player.setPosition(Tilepos);
					player.setStartPos(Tilepos);
					player.setNextLevel(false);
					continue;
				}

				else if (isItemsType(currline[col]))
					(KEY_SIGN == currline[col]) ? keyAlloc(p, keys) : snowAlloc(p, snows);

				else if (isEnemyType(currline[col]))
				{
					enemyAlloc(p, enemies);
					isTower(p, row, col);
				}

				else if (isStaticType(currline[col]))
				{
					staticAlloc(p, m_static_vec);
					boardGraph[row][col] = false;
					isCastle(p, row, col);
					isHomeEnemy(p, row, col);
				}
			}
		}
		randKeyNum(keys);
		return true;
	}
	catch (std::exception&)
	{
		cout << "there is error with file";
		exit(EXIT_FAILURE);
	}
	return true;// compiller dont shout
	

}
//--------------------------fillGraphObstacle---------------------------------------------
//function that accepts position on the board, row, and column and updates the relevant cells to false
void Board::fillGraphObstacle(sf::Vector2i pos,int row,int col)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			m_boardGraph[pos.x + i][pos.y + j] = false;

}
void Board::rangeDim(const int & row, const int & col) const
{
	
		if (row <= 0 || col <= 0 || row > 100 || col > 100)
		 throw exception();
	
		

}

//--------------------------readFromFile-----------------------------------------------------
void Board::readFromFile(std::ifstream & inputFile, int dimY, std::string & currline)
// function that checks the integrity of a file, If the file is correct, it reads rows
{

	if (inputFile.eof()) // case there error with file
	{
		
		currline.clear();
		currline.resize(dimY, ' '); //make empty curr line
		throw std::exception();
	}
	else
	{
		getline(inputFile, currline); // the currline of the file
		if (static_cast<int>(currline.size()) < dimY) // case there error in the filefill with space
		{
			currline.resize(dimY, ' ');
			throw std::exception();
		}
	}

}
//----------------------------checkFile--------------------------------------------
//function that checks whether the reading from the file was successful, if it does not throw an exception
void Board::checkFile(std::ifstream & inputFile, int dimY, std::string & currline)
{
	
		readFromFile(inputFile, dimY, currline);

}
//------------------------openFile----------------------------------------------
//function that accepts the file and a level number and loads the level
void Board::openFile(std::ifstream &inputFile, int level)
{
	std::string name = "level_" + std::to_string(level) + ".txt"; // name of file 

	inputFile.open(name); // open level file
}
//----------------------randKeyNum--------------------------------------------------
// function that rand out which of the existing keys will be correct
void Board::randKeyNum(std::vector<std::unique_ptr<Key>>& keys)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, keys.size()-1); // distribution in range 1 - size key
	keys[dist6(rng)].get()->setKey(true);
}
//-----------------------resetGraphTrue---------------------------------------------
//function that reset Graph to True
void Board::resetGraphTrue(int dimX, int dimY)
{
	m_boardGraph.resize(0);
	m_boardGraph.resize(dimX);
	for (int i = 0; i < m_boardGraph.size(); i++)
	{
		m_boardGraph[i].resize(dimY);
		for (int j = 0; j < m_boardGraph[0].size(); j++)
			m_boardGraph[i][j] = true;
	}

}
//----------------------isEnemyType------------------------------------------------------
//function that return true if obj is enemy
bool Board::isEnemyType(const char & type) const
{
	return (STUPID_GAURD_SIGN == type ||
		SCOUT_SIGN == type || WATCH_TOWER_SIGN == type);
	
}
//----------------------isStaticType-----------------------------------------------------
//function that return true if obj is static
bool Board::isStaticType(const char & type) const
{
	return (WALL_SIGN == type || CASTLE_SIGN == type || RAND_MACHINE_SIGN == type);
}
//-------------------isItemsType----------------------------------------------------------
//function that return true if obj is item
bool Board::isItemsType(const char & type) const
{
	return (KEY_SIGN == type || SNOW_SIGN == type);
}
//----------------------keyAlloc---------------------------------------------------------
//function that create key and insert to vector 
void Board::keyAlloc(Creature* creature, std::vector<std::unique_ptr <Key>> &keys)const
{
	Key* q = dynamic_cast<Key*>(creature);
	std::unique_ptr<Key> uq(q);
	keys.emplace_back(std::move(uq));
	if (keys.back() != nullptr)
	{
		keys.back().get()->setKey(false);
		keys.back()->setPosition(Tilepos);
	}

}
//----------------------snowAlloc-----------------------------------------------------------
//function that create snow and insert to vector 
void Board::snowAlloc(Creature * creature, std::vector<std::unique_ptr<Snow>>& snows) const
{
	Snow* q = dynamic_cast<Snow*>(creature);
	std::unique_ptr<Snow> uq(q);
	snows.emplace_back(std::move(uq));
	if (snows.back() != nullptr)
		snows.back()->setPosition(Tilepos);
}
//---------------------enemyAlloc------------------------------------------------------------
//function that create kind of enemy and insert to vector 
void Board::enemyAlloc(Creature * creature, std::vector<std::unique_ptr<Enemy>>& enemies) const
{
	Enemy* q = dynamic_cast<Enemy*>(creature);
	std::unique_ptr<Enemy> uq(q);
	enemies.emplace_back(std::move(uq));
	enemies.back()->setPosition(Tilepos);
	enemies.back()->setStartPos(Tilepos);

}
//-----------------------staticAlloc----------------------------------------------------------
//function that create static obj and insert to vector 
void Board::staticAlloc(Creature * creature, std::vector<std::unique_ptr<NoneAlive>>& m_static_vec) const
{
	NoneAlive* q = dynamic_cast<NoneAlive*>(creature);
	std::unique_ptr<NoneAlive> uq(q);
	m_static_vec.emplace_back(std::move(uq));
	m_static_vec.back()->setPosition(Tilepos);
}
//----------------------isCastle---------------------------------------------------------------
//function that checks if this is a castle, then updates the position of the door and calls a function that 
//inserts false to  m_boardGraph in the castle's cells
void Board::isCastle(Creature * creature,int row,int col) 
{
	auto castle = dynamic_cast<Castle*>(creature);
	if (castle)
	{
		castle->setPosDoor();
		fillGraphObstacle(sf::Vector2i{ row,col }, 5, 5);	
	}
}
//--------------------isHomeEnemy--------------------------------------------------------------
//function that checks if this is a home, then calls a function that 
//inserts false to  m_boardGraph in the home's cells
void Board::isHomeEnemy(Creature * creature, int row, int col)
{
	auto home = dynamic_cast<RandMachine*>(creature);
	if (home)
	{
		fillGraphObstacle(sf::Vector2i{ row,col }, 2, 4);
	}

}
//--------------------isTower-----------------------------------------------------------------
//function that checks if this is a tower, then updates the position of the range and calls a function that 
//inserts false to  m_boardGraph in the tower's cells
void Board::isTower(Creature * creature, int row, int col)
{
	auto tower = dynamic_cast<WatchTower*>(creature);
	if (tower)
	{
		fillGraphObstacle(sf::Vector2i{ row,col }, 4, 3);
		tower->setPosRange();
		tower->setPosTowerCenter();
	}

}
//---------------------getCreatureEnumFromChar------------------------------------------------
//function that get Char and return Creature Enum
CREATURE_T Board::getCreatureEnumFromChar(const char & _char) const
{
	switch (_char)
	{
		case SCOUT_SIGN: return SCOUT_T;
		case STUPID_GAURD_SIGN: return STUPID_GAURD_T;
		case WATCH_TOWER_SIGN: return WACTH_TOWER_T;
		case WALL_SIGN: return WALL_T;
		case EMPTY_SIGN: return EMPTY_T;
		case ROCK_SIGN: return ROCK_T;
		case CASTLE_SIGN: return CASTLE_T;
		case RAND_MACHINE_SIGN:return RAND_MACHINE_T;
		case KEY_SIGN: return KEY_T;
		case SNOW_SIGN:return SNOW_T;
	}
	return CREATURE_T(0); //default
}


