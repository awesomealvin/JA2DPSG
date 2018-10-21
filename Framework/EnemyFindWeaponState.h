#ifndef __ENEMYFINDWEAPONSTATE_H__
#define __ENEMYFINDWEAPONSTATE_H__
#include "EnemyState.h"

class Weapon;
class EnemyFindWeaponState :
	public EnemyState
{
public:
	static EnemyFindWeaponState& GetInstance();
	~EnemyFindWeaponState();

	static void DestroyInstance();

	void Enter(Enemy& e) override;
	void Execute(Enemy& e, float dt) override;
	void Exit(Enemy& e) override;

protected:
	Weapon* GetNearestWeapon(b2Vec2 currentPosition, Enemy* e);
	void RemoveWeaponFromLevel(Weapon* weapon);

private:
	EnemyFindWeaponState();
	EnemyFindWeaponState(const EnemyFindWeaponState& enemyFindWeaponState);
	EnemyFindWeaponState& operator=(const EnemyFindWeaponState& enemyFindWeaponState);

	static EnemyFindWeaponState* sm_pInstance;

};

#endif

