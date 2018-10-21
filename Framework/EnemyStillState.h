#ifndef __ENEMYSTILLSTATE_H__
#define __ENEMYSTILLSTATE_H__
#include "EnemyState.h"
class EnemyStillState :

	public EnemyState
{

public:
	static EnemyStillState& GetInstance();
	~EnemyStillState();

	static void DestroyInstance();

	void Enter(Enemy& e) override;
	void Execute(Enemy& e, float dt) override;
	void Exit(Enemy& e) override;

private:
	EnemyStillState();
	EnemyStillState(const EnemyStillState& enemyStillState);
	EnemyStillState& operator=(const EnemyStillState& enemyStillState);

protected:
	static EnemyStillState* sm_pInstance;
};

#endif
