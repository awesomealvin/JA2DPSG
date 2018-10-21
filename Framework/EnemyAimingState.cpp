#include "EnemyAimingState.h"

#include "Blackboard.h"
#include "MyUtility.h"
#include "game.h"

EnemyAimingState* EnemyAimingState::sm_pInstance = 0;

void EnemyAimingState::Enter(Enemy & e)
{

}

void EnemyAimingState::Execute(Enemy & e, float dt)
{
	b2Vec2 playerPosition = Blackboard::GetInstance().GetPlayerPosition();
	playerPosition.y += e.m_handYOffset * PTM;

	b2Vec2 aimingLocation = e.GetAimingLocation();
	b2Vec2 newAimingLocation = MyUtility::Lerp(aimingLocation, playerPosition, dt);

	e.SetAimingLocation(newAimingLocation);

	// Check for shoot
	float shootingWidth = 1.0f;
	b2Vec2 difference = MyUtility::GetDirection(newAimingLocation, playerPosition);
	float length = abs(MyUtility::GetMagnitude(difference));

	if (e.HasWeapon())
	{
		e.AddCurrentShootingTime(dt);
		if (length <= shootingWidth)
		{
			if (e.CanShoot())
			{
				e.Shoot();
				e.ResetCurrentShootingTime();
			}
		}
	}


}

void EnemyAimingState::Exit(Enemy & e)
{

}

EnemyAimingState::EnemyAimingState()
{
}


EnemyAimingState & EnemyAimingState::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new EnemyAimingState();
	}

	return (*sm_pInstance);
}

EnemyAimingState::~EnemyAimingState()
{
}

void EnemyAimingState::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}
