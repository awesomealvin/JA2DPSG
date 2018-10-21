#ifndef __ENEMYSTATE_H__
#define __ENEMYSTATE_H__

#include "Enemy.h"

class Enemy;

class EnemyState
{
public:
	virtual void Enter(Enemy& e) = 0;
	virtual void Execute(Enemy& e, float dt) = 0;
	virtual void Exit(Enemy& e) = 0;
};

#endif 