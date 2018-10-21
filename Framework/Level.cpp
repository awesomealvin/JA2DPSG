#include "Level.h"

#include "Player.h"
#include "ObjectPool.h"
#include <algorithm>
#include "HUD.h"

Level::Level()
{
}


Level::~Level()
{
}

void Level::Initialise(int levelNumber)
{
	m_levelNumber = levelNumber;
}

void Level::InsertData(EntityTypes entityType, Vector2 position)
{
	EntityData newData;
	newData.m_entityType = entityType;
	newData.m_position = position;

	m_entityDataDetails.push_back(newData);
}

void Level::LoadLevel(Player& player)
{
	ClearLevel(player);

	std::vector<EntityData>::iterator it;
	for (it = m_entityDataDetails.begin(); it != m_entityDataDetails.end(); ++it)
	{
		EntityData data = *it;

		Entity* entity;
		if (data.m_entityType == EntityTypes::PLAYER)
		{
			entity = &player;
			player.SetPosition(data.m_position);
		}
		else
		{
			entity = ObjectPool::GetInstance().GetEntity(data.m_entityType);
			entity->Activate(data.m_position);
			entity->Reset();

			if (entity->GetType() == EntityTypes::WEAPONS)
			{
				m_pWeapons.push_back(static_cast<Weapon*>(entity));
			}
			if (entity->GetType() == EntityTypes::ENEMIES)
			{
				++m_enemiesRemaining;
			}
		}

		// Offset the objects to spawn on the top left (because of box2d)
		Vector2 positionOffset = entity->GetPixelPosition();
		positionOffset.m_x += entity->GetWidth() / 2;
		positionOffset.m_y += entity->GetHeight() / 2;
		entity->SetPosition(positionOffset);
	}

	HUD::GetInstance().SetEnemiesRemainingText(m_enemiesRemaining);
}

void Level::ClearLevel(Player & player)
{
	player.Reset();
	ObjectPool::GetInstance().SetAllDead();
	m_pWeapons.clear();
	
	m_enemiesRemaining = 0;
	HUD::GetInstance().SetEnemiesRemainingText(m_enemiesRemaining);
}


std::vector<Weapon*> Level::GetWeaponVector()
{
	return m_pWeapons;
}

void Level::ClearWeapon(Weapon * weapon)
{
	m_pWeapons.erase(std::remove(m_pWeapons.begin(), m_pWeapons.end(), weapon), m_pWeapons.end());
}

int Level::DecrementEnemiesRemaining()
{
	--m_enemiesRemaining;
	HUD::GetInstance().SetEnemiesRemainingText(m_enemiesRemaining);

	return m_enemiesRemaining;
	// CHANGE LEVEL

}
