#ifndef __ENEMYHEADPARTICLE_H__
#define __ENEMYHEADPARTICLE_H__
#include "entity.h"

class EnemyHeadParticle :
	public Entity
{
public:
	EnemyHeadParticle();
	~EnemyHeadParticle();

	void InitialiseBody(b2World* world, Vector2 position);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	EntityTypes GetType() const;
};

#endif