#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "entity.h"
#include "Vector2.h"
class Character;

class Weapon :
	public Entity
{
public:
	Weapon();
	
	~Weapon();

	void InitialiseBody(b2World* world, Vector2 position);
	void Draw(BackBuffer& backBuffer);
	void Process(float deltaTime);

	void OnPickup();
	void FilterIgnorePlayer();
	void FilterAddPlayer();

	void SetFlip(bool flip);

	EntityTypes GetType() const;

	Vector2 GetWeaponOffset() const;
	Vector2 GetHandOffset() const;

	b2Vec2 GetShootingPoint() const;

	void Shoot(float angle, b2Vec2 direction);
	void SetPlayerOwned(bool playerOwned);
	bool IsPlayerOwned() const;

	void SetOwned(bool owned);
	bool IsOwned() const;

	bool IsFlipped() const;

	void SetupShootingDelay();
	void ProcessShootingDelay(float deltaTime);
	bool EnemyCanShoot() const;

	Character* GetOwner();
	void SetOwner(Character* owner);

protected:
	int m_height;
	int m_width;

	bool m_flip;

	Vector2 m_weaponOffset;
	Vector2 m_shootingPoint;
	Vector2 m_handOffset;

	Character* m_owner;
	bool m_playerOwned; // Owned by the player
	bool m_isOwned; // Owned by enemies

	float m_minEnemyShootingDelay;
	float m_maxEnemyShootingDelay;
	float m_enemyShootingDelay;
	float m_currentEnemyShootingTime;
};

#endif

