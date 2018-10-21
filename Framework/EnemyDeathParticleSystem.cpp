#include "EnemyDeathParticleSystem.h"

#include "EnemyDeathParticle.h"
#include "ObjectPool.h"
#include "game.h"
#include "entity.h"
#include "EnemyHeadParticle.h"
#include "MyUtility.h"
EnemyDeathParticleSystem* EnemyDeathParticleSystem::sm_pInstance = 0;

EnemyDeathParticleSystem::EnemyDeathParticleSystem()
{

}


EnemyDeathParticleSystem & EnemyDeathParticleSystem::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new EnemyDeathParticleSystem();
	}

	return (*sm_pInstance);
}

EnemyDeathParticleSystem::~EnemyDeathParticleSystem()
{
}

void EnemyDeathParticleSystem::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

void EnemyDeathParticleSystem::Spawn(b2Vec2 position, b2Vec2 contactPoint)
{
	EnemyDeathParticle* topLeft = ObjectPool::GetInstance().GetEnemyTopLeftDeathParticle();
	EnemyDeathParticle* topRight = ObjectPool::GetInstance().GetEnemyTopRightDeathParticle();
	EnemyDeathParticle* bottomLeft = ObjectPool::GetInstance().GetEnemyBottomDeathParticle();
	EnemyDeathParticle* bottomRight = ObjectPool::GetInstance().GetEnemyBottomDeathParticle();
	EnemyHeadParticle* head = ObjectPool::GetInstance().GetEnemyHeadParticle();


	/*SetParticlePosition(topLeft, position, Vector2(-5, 20));
	SetParticlePosition(topRight, position, Vector2(5, 20));
	SetParticlePosition(bottomLeft, position, Vector2(-5, -6));
	SetParticlePosition(bottomRight, position, Vector2(5, -6));*/

	SetParticlePosition(topLeft, position, Vector2(-5, -6), contactPoint);
	SetParticlePosition(topRight, position, Vector2(5, -6), contactPoint);
	SetParticlePosition(bottomLeft, position, Vector2(-5, 5), contactPoint);
	SetParticlePosition(bottomRight, position, Vector2(5, 5), contactPoint);
	SetParticlePosition(head, position, Vector2(0, -25), contactPoint);
}

void EnemyDeathParticleSystem::SetParticlePosition(Entity * particle, b2Vec2 position, Vector2 offset, b2Vec2 contactPoint)
{
	if (particle != 0)
	{
		b2Vec2 newPosition;
		newPosition.x = position.x + (offset.m_x * PTM);
		newPosition.y = position.y + (offset.m_y * PTM);
		particle->SetDeadWithDelay(false);
		particle->SetPositionWithDelay(newPosition);
		particle->StartDecay();
		AddExplosionForce(particle, contactPoint, newPosition);
	}
}

void EnemyDeathParticleSystem::AddExplosionForce(Entity * particle, b2Vec2 collisionPoint, b2Vec2 particlePosition)
{
	b2Vec2 direction = MyUtility::GetDirection(collisionPoint, particlePosition);
	direction.x *= 20;
	direction.y *= 20;
	particle->AddForceWithDelay(direction);
}
