#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "Vector2.h"

#include "entity.h"
#include <vector>

class Player;
class Weapon;

struct EntityData;

class Level
{
public:
	Level();
	~Level();

	void Initialise(int levelNumber);
	void InsertData(EntityTypes entityType, Vector2 position);

	void LoadLevel(Player& player);
	void ClearLevel(Player & player);

	std::vector<Weapon*> GetWeaponVector();
	void ClearWeapon(Weapon* weapon);

	int DecrementEnemiesRemaining();

protected:
	struct EntityData {
		EntityTypes m_entityType;
		Vector2 m_position;
	};
	std::vector<EntityData> m_entityDataDetails;

	int m_levelNumber;

	int m_enemiesRemaining;

	std::vector<Weapon*> m_pWeapons;

};

#endif