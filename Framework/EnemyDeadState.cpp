#include "EnemyDeadState.h"

#include "Enemy.h"
#include "EnemyStillState.h"
#include "EnemyDeathParticleSystem.h"
#include "EnemyDeathParticle.h"
#include "ObjectPool.h"
#include "LevelManager.h"

EnemyDeadState* EnemyDeadState::sm_pInstance = 0;

EnemyDeadState & EnemyDeadState::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new EnemyDeadState();
	}

	return (*sm_pInstance);
}

EnemyDeadState::~EnemyDeadState()
{
}

EnemyDeadState::EnemyDeadState()
{
}

void EnemyDeadState::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

void EnemyDeadState::Enter(Enemy & e)
{
	e.SpawnBloodExplosion(30, 50);

	//e.SetBodyCanRotate(true);
	e.SetDeadWithDelay(true);
	EnemyDeathParticleSystem::GetInstance().Spawn(e.GetWorldPosition(), e.m_lastBulletContactWorldPosition);
	LogManager::GetInstance().Log("Enemy Dead");
	LevelManager::GetInstance().DecrementEnemiesRemainingOnCurrentLevel();

}

void EnemyDeadState::Execute(Enemy & e, float dt)
{
	// Start Death Animation Thing
}

void EnemyDeadState::Exit(Enemy & e)
{
	e.ChangeState(&EnemyStillState::GetInstance());
	

	
}
