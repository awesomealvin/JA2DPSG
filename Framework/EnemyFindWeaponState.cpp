#include "EnemyFindWeaponState.h"

#include "Weapon.h"
#include "Level.h"
#include "LevelManager.h"
#include <vector>
#include "MyUtility.h"
#include "DebugUI.h"
#include "EnemyFollowPlayerState.h"


EnemyFindWeaponState* EnemyFindWeaponState::sm_pInstance = 0;

void EnemyFindWeaponState::Enter(Enemy & e)
{
	if (e.m_foundWeapon == 0)
	{
		e.m_foundWeapon = GetNearestWeapon(e.GetWorldPosition(), &e);
	}
}

void EnemyFindWeaponState::Execute(Enemy & e, float dt)
{
	if (e.m_foundWeapon != 0)
	{
		if (e.m_foundWeapon->IsOwned())
		{
			e.m_foundWeapon = 0;
			Enter(e);
		}

		b2Vec2 weaponPosition = e.GetWorldPosition();
		b2Vec2 enemyPosition = e.m_foundWeapon->GetWorldPosition();

		b2Vec2 direction = (MyUtility::GetDirection(weaponPosition, enemyPosition));
		float distanceX = abs(direction.x);
		float distanceY = abs(direction.y);
		//DebugUI::GetInstance().SetLine(1, std::to_string(distanceX));
		if (distanceX <= 0.5f)
		{
			e.Stop();

			if (enemyPosition.y < weaponPosition.y)
			{
				e.Jump();
			}
		}
		else if (enemyPosition.x > weaponPosition.x)
		{
			e.MoveRight();
			e.SetAimingLocation(e.GetWorldPosition());

		}
		else if (enemyPosition.x < weaponPosition.x)
		{
			e.MoveLeft();
			e.SetAimingLocation(e.GetWorldPosition());

		} 

		if (abs(MyUtility::GetMagnitude(direction)) < 0.5f)
		{
			// pickup weapon
			e.SetWeapon(e.m_foundWeapon);
			RemoveWeaponFromLevel(e.m_foundWeapon); // so that other enemies won't search for it again
			e.ChangeState(&EnemyFollowPlayerState::GetInstance());
			e.SetAimingRange();
		}

	}
}

void EnemyFindWeaponState::Exit(Enemy & e)
{

}

Weapon * EnemyFindWeaponState::GetNearestWeapon(b2Vec2 currentPosition, Enemy* e)
{
	Level* level = LevelManager::GetInstance().GetCurrentLevel();

	std::vector<Weapon*> weapons = level->GetWeaponVector();

	Weapon* currentWeapon = 0;
	float currentDistance = FLT_MAX;
	for (std::vector<Weapon*>::iterator it = weapons.begin();
		it != weapons.end(); ++it)
	{
		Weapon* weaponToSearch = *it;
		b2Vec2 direction = MyUtility::GetDirection(
			weaponToSearch->GetWorldPosition(), currentPosition);

		float nextDistance = abs(MyUtility::GetMagnitude(direction));
		if (nextDistance < currentDistance)
		{
			currentDistance = nextDistance;
			currentWeapon = weaponToSearch;
		}
	}

	return currentWeapon;
}

void EnemyFindWeaponState::RemoveWeaponFromLevel(Weapon * weapon)
{
	Level* level = LevelManager::GetInstance().GetCurrentLevel();
	level->ClearWeapon(weapon);
}

EnemyFindWeaponState::EnemyFindWeaponState()
{

}


EnemyFindWeaponState & EnemyFindWeaponState::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new EnemyFindWeaponState();
	}

	return (*sm_pInstance);
}

EnemyFindWeaponState::~EnemyFindWeaponState()
{

}

void EnemyFindWeaponState::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}
