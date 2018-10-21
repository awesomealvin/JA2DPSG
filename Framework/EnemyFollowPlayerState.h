#ifndef __ENEMYFOLLOWPLAYERSTATE_H__
#define __ENEMYFOLLOWPLAYERSTATE_H__
#include "EnemyState.h"
class EnemyFollowPlayerState :
	public EnemyState
{
public:
	static EnemyFollowPlayerState& GetInstance();
	~EnemyFollowPlayerState();

	static void DestroyInstance();

	void Enter(Enemy& e) override;
	void Execute(Enemy& e, float dt) override;
	void Exit(Enemy& e) override;


private:
	EnemyFollowPlayerState();
	EnemyFollowPlayerState(const EnemyFollowPlayerState& enemyFollowPlayerState);
	EnemyFollowPlayerState& operator=(const EnemyFollowPlayerState& enemyFollowPlayerState);

	static EnemyFollowPlayerState* sm_pInstance;
};

#endif

