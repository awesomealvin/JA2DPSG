#ifndef __ENEMYDEADSTATE_H__
#define __ENEMYDEADSTATE_H__

#include "EnemyState.h"

class EnemyDeadState :
	public EnemyState
{
public:
	static EnemyDeadState& GetInstance();
	~EnemyDeadState();

	static void DestroyInstance();

	void Enter(Enemy& e) override;
	void Execute(Enemy& e, float dt) override;
	void Exit(Enemy& e) override;

private:
	EnemyDeadState();
	EnemyDeadState(const EnemyDeadState& enemyDeadState);
	EnemyDeadState& operator=(const EnemyDeadState& enemyDeadState);

protected:
	static EnemyDeadState* sm_pInstance;
};

#endif

