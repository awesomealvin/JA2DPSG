#include "EnemyStillState.h"

#include "EnemyFindWeaponState.h"
#include "EnemyFollowPlayerState.h"

EnemyStillState* EnemyStillState::sm_pInstance = 0;

void EnemyStillState::Enter(Enemy & e)
{
	
}

void EnemyStillState::Execute(Enemy & e, float dt)
{
	if (!e.HasWeapon())
	{
		e.ChangeState(&EnemyFindWeaponState::GetInstance());
	}
	else
	{
		e.ChangeState(&EnemyFollowPlayerState::GetInstance());
	}
}

void EnemyStillState::Exit(Enemy & e)
{
}


EnemyStillState & EnemyStillState::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new EnemyStillState();
	}

	return (*sm_pInstance);
}

EnemyStillState::~EnemyStillState()
{
	
}

EnemyStillState::EnemyStillState()
{

}


void EnemyStillState::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}
