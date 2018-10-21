#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"

class Entity;
class EnemyState;
class Weapon;

class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();

	void Process(float deltaTime);

	EntityTypes GetType() const;
	void OnCollisionBegin(Entity* other, b2Contact* contact);
	void OnCollisionPostSolve(Entity* other, b2Contact* contact, const b2ContactImpulse* impulse);

	void ChangeState(EnemyState* state);

	bool HasFoundPlayer() const;
	void SetFoundPlayer(bool found);

	void SetAimingLocation(b2Vec2 aimingLocation);
	b2Vec2 GetAimingLocation();

	Weapon* m_foundWeapon;

	bool CanShoot() const;
	void AddCurrentShootingTime(float deltaTime);
	void ResetCurrentShootingTime();

	void Reset() override;

	void SetAimingRange();
	float GetAimingRange() const;
protected:
	EnemyState* m_currentState;

	void SetHandPosition();

	b2Vec2 m_aimingLocation;

	bool m_foundPlayer;

	float m_minAimingRange;
	float m_maxAimingRange;
	float m_aimingRange;


};

#endif

