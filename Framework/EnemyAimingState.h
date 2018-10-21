#ifndef __ENEMYAIMINGSTATE_H__
#define __ENEMYAIMINGSTATE_H__

#include "EnemyState.h"
class EnemyAimingState :
	public EnemyState
{
public:
	static EnemyAimingState& GetInstance();
	~EnemyAimingState();

	static void DestroyInstance();

	void Enter(Enemy& e) override;
	void Execute(Enemy& e, float dt) override;
	void Exit(Enemy& e) override;


private:
	EnemyAimingState();
	EnemyAimingState(const EnemyAimingState& enemyAimingState);
	EnemyAimingState& operator=(const EnemyAimingState& enemyAimingState);

	static EnemyAimingState* sm_pInstance;
};

#endif
