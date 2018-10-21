#include "LevelManager.h"

#include "ObjectPool.h"
#include "entity.h"
#include "Vector2.h"
#include "logmanager.h"
#include "IniParser.h"
#include "Player.h"
#include "Blackboard.h"
#include "HUD.h"
#include "game.h"

#include "Level.h"

LevelManager* LevelManager::sm_pInstance = 0;

LevelManager::LevelManager()
	: NUMBER_OF_LEVELS(10)
{
}


LevelManager & LevelManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new LevelManager();
	}

	return (*sm_pInstance);
}

LevelManager::~LevelManager()
{
	for (int i = 0; i < NUMBER_OF_LEVELS; ++i)
	{
		delete m_pLevels[i];
		m_pLevels[i] = 0;
	}

	delete[] m_pLevels;
	m_pLevels = 0;
}

void LevelManager::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

void LevelManager::Initialise(Player& player , int startingLevel)
{
	m_currentLevel = startingLevel;
	m_pLevels = new Level*[NUMBER_OF_LEVELS];
	for (int i = 0; i < NUMBER_OF_LEVELS; ++i)
	{
		m_pLevels[i] = new Level();
		m_pLevels[i]->Initialise(i);

		std::string fileLocation = "..\\bin\\data\\levels\\levellayout" + std::to_string(i) + ".ini";

		IniParser p;
		p.LoadIniFile(fileLocation);

		int size = p.GetMapLength();

		for (int k = 0; k < size; ++k)
		{
			std::string section = std::to_string(k);
			std::string stringEntityType = p.GetValueAsString(section, "type");
			EntityTypes entityType = GetType(stringEntityType);
			float x = p.GetValueAsFloat(section, "x");
			float y = p.GetValueAsFloat(section, "y");
			Vector2 position(x, y);

			/*Entity* entity;
			if (entityType == EntityTypes::PLAYER)
			{
				LogManager::GetInstance().Log("Player found in ini file");
				entity = &player;
				player.SetPosition(Vector2(x, y));
			}
			else
			{
				entity = ObjectPool::GetInstance().GetEntity(entityType);
				entity->Activate(Vector2(x, y));
			}*/

			m_pLevels[i]->InsertData(entityType, position);

			// Offset the objects to spawn on the top left (because of box2d)
			/*Vector2 positionOffset = entity->GetPixelPosition();
			positionOffset.m_x += entity->GetWidth() / 2;
			positionOffset.m_y += entity->GetHeight() / 2;
			entity->SetPosition(positionOffset);*/
		}
	}
}


void LevelManager::ResetLevel(int currentLevel, Player & player)
{
	HUD::GetInstance().SetCurrentLevelText(currentLevel);
	m_pLevels[currentLevel]->LoadLevel(player);
	Blackboard::GetInstance().SetPlayer(player);

}

void LevelManager::ResetLevel(Player & player)
{
	HUD::GetInstance().SetCurrentLevelText(m_currentLevel);
	m_pLevels[m_currentLevel]->LoadLevel(player);
	Blackboard::GetInstance().SetPlayer(player);
}


void LevelManager::ClearLevel(Player & player)
{
	player.Reset();
	ClearLevel();
}

void LevelManager::ClearLevel()
{
	ObjectPool::GetInstance().SetAllDead();
}

Level * LevelManager::GetCurrentLevel()
{
	return m_pLevels[m_currentLevel];
}

void LevelManager::DecrementEnemiesRemainingOnCurrentLevel()
{
	Level* level = GetCurrentLevel();
	int enemiesRemaining = level->DecrementEnemiesRemaining();
	if (enemiesRemaining <= 0)
	{
		++m_currentLevel;
		if (m_currentLevel > NUMBER_OF_LEVELS - 1)
		{
			m_currentLevel = 0;
			Game::GetInstance().StartGameOver(true);
		}
		else
		{
			Game::GetInstance().StartNextLevel();
		}
	}
}

EntityTypes LevelManager::GetType(std::string str)
{
	EntityTypes returnType = EntityTypes::PLATFORM;
	if (str == "wall")
	{
		returnType = EntityTypes::WALL;
	}
	else if (str == "platform")
	{
		returnType = EntityTypes::PLATFORM;
	}
	else if (str == "pistol")
	{
		returnType = EntityTypes::PISTOL;
	}
	else if (str == "player")
	{
		returnType = EntityTypes::PLAYER;
	}
	else if (str == "enemy")
	{
		returnType = EntityTypes::ENEMIES;
	}

	return returnType;
}
