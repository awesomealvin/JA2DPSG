#ifndef __ENEMYDEATHPARTICLESYSTEM_H__
#define __ENEMYDEATHPARTICLESYSTEM_H__

#include "Box2D/Box2D.h"
#include "Vector2.h"

class EnemyDeathParticle;
class EnemyHeadParticle;
class Entity;

class EnemyDeathParticleSystem
{
public:
	static EnemyDeathParticleSystem& GetInstance();

	~EnemyDeathParticleSystem();
	static void DestroyInstance();

	void Spawn(b2Vec2 position, b2Vec2 contactPoint);

	void SetParticlePosition(Entity* particle, b2Vec2 position, Vector2 offset, b2Vec2 contactPoint);
	void AddExplosionForce(Entity* particle, b2Vec2 collisionPoint, b2Vec2 particlePosition);

private:
	EnemyDeathParticleSystem();
	EnemyDeathParticleSystem(const EnemyDeathParticleSystem& enemyDeathParticleSystem);
	EnemyDeathParticleSystem& operator=(const EnemyDeathParticleSystem& enemyDeathParticleSystem);

protected:
	static EnemyDeathParticleSystem* sm_pInstance;
};

#endif