#include "EnemyFollowPlayerState.h"
#include "Blackboard.h"
#include "MyUtility.h"
#include "EnemyStillState.h"
#include "DebugUI.h"
#include "EnemyAimingState.h"
#include "game.h"
//#include <string>

EnemyFollowPlayerState* EnemyFollowPlayerState::sm_pInstance = 0;

void EnemyFollowPlayerState::Enter(Enemy & e)
{
	e.SetFoundPlayer(Blackboard::GetInstance().HasFoundPlayer());
}

void EnemyFollowPlayerState::
Execute(Enemy & e, float dt)
{
	if (e.HasFoundPlayer())
	{
		b2Vec2 playerPos = Blackboard::GetInstance().GetPlayerPosition();
		b2Vec2 enemyPos = e.GetWorldPosition();
		b2Vec2 direction = MyUtility::GetInstance().GetDirection(
			enemyPos, playerPos);

		float distance = abs(MyUtility::GetInstance().GetMagnitude(direction));

		DebugUI::GetInstance().SetLine(2, std::to_string(distance));

		float shootingDistance = e.GetAimingRange();
		if (abs(direction.x) <= 1.0f && distance > shootingDistance)
		{
			if (enemyPos.y > playerPos.y)
			{
				e.Jump();
			}
		}
		else if (distance < shootingDistance)
		{
			e.Stop();
			// Change state to aiming
			e.ChangeState(&EnemyAimingState::GetInstance());
		}
		else if (enemyPos.x > playerPos.x)
		{
			e.MoveLeft();
			b2Vec2 aimingLocation = e.GetWorldPosition();
			aimingLocation.x += e.GetWidth() * PTM;
			e.SetAimingLocation(aimingLocation);

		}
		else if (enemyPos.x < playerPos.x)
		{
			e.MoveRight();
			b2Vec2 aimingLocation = e.GetWorldPosition();
			aimingLocation.x -= e.GetWidth() * PTM;
			e.SetAimingLocation(aimingLocation);
			e.SetAimingLocation(e.GetWorldPosition());
		}
		//e.SetAimingLocation(e.GetWorldPosition());

		DebugUI::GetInstance().SetLine(3, "Enemy Position Y: " + std::to_string(enemyPos.y));
		DebugUI::GetInstance().SetLine(4, "Player Position Y: " +std::to_string(playerPos.y));
	}
}

void EnemyFollowPlayerState::Exit(Enemy & e)
{
}

EnemyFollowPlayerState::EnemyFollowPlayerState()
{

}


EnemyFollowPlayerState & EnemyFollowPlayerState::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new EnemyFollowPlayerState();
	}

	return (*sm_pInstance);
}

EnemyFollowPlayerState::~EnemyFollowPlayerState()
{
	
}

void EnemyFollowPlayerState::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}
