#ifndef __LEVELMANAGER_H__
#define __LEVELMANAGER_H__

#include <string>
#include "EntityTypes.h"

class Level;
class Player;

class LevelManager
{
public:
	static LevelManager& GetInstance();
	~LevelManager();

	static void DestroyInstance();

	void Initialise(Player& player, int startingLevel);
	void ResetLevel(int currentLevel, Player& player);
	void ResetLevel(Player& player);

	void ClearLevel(Player& player);
	void ClearLevel();

	Level* GetCurrentLevel();
	void DecrementEnemiesRemainingOnCurrentLevel();

	EntityTypes GetType(std::string str);

private:
	LevelManager();
	LevelManager(const LevelManager& levelManager);
	LevelManager& operator=(const LevelManager& levelManager);

protected:
	Level** m_pLevels;
	const int NUMBER_OF_LEVELS;

	int m_currentLevel;

	static LevelManager* sm_pInstance;

};

#endif

