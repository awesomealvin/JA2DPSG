#ifndef __BULLET_H__
#define __BULLET_H__
#include "entity.h"
#include "Weapon.h"
class Bullet :
	public Entity
{
public:
	Bullet();
	~Bullet();

	void InitialiseBody(b2World* world, Vector2 position);

	void Draw(BackBuffer& backBuffer);
	void Process(float deltaTime);
	EntityTypes GetType() const;

	void OnCollisionBegin(Entity * other, b2Contact* contact) override;
	void OnCollisionPreSolve(Entity* other, b2Contact* contact, const b2Manifold* oldManifold) override;

	void Reset() override;

	void SetOwner(bool playerOwned, Weapon* weaponOwner);
	Character* GetEntityOwner();

protected:
	bool m_playerOwned;
	Weapon* m_weaponShotFrom;
	Character* m_owner;
};


#endif
