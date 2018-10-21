#ifndef __ENEMYDEATHPARTICLE_H__
#define __ENEMYDEATHPARTICLE_H__
#include "entity.h"
class EnemyDeathParticle :
	public Entity
{
public:
	EnemyDeathParticle();
	~EnemyDeathParticle();

	void InitialiseBody(b2World* world, Vector2 position);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	EntityTypes GetType() const;

};

#endif

