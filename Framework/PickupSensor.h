#ifndef __PICKUPSENSOR_H__
#define __PICKUPSENSOR_H__

#include "Box2D/Box2D.h"
#include "entity.h"
#include "EntityTypes.h"

class Player;
class Weapon;

class PickupSensor : public Entity
{
public:
	PickupSensor();
	~PickupSensor();

	void Activate(float x, float y, Weapon* thrownWeapon);
	void Activate(b2Vec2 position, Weapon* thrownWeapon);
	void InitialiseBody(b2World* world);

	void SetPlayer(Player* player);

	void Draw(BackBuffer & backBuffer);
	void Process(float deltaTime);

	EntityTypes GetType() const;

	void OnCollisionBegin(Entity * other, b2Contact* contact) override;


protected:
	float m_radius;

	Player* m_player;

	Weapon* m_weaponToPickup;

	bool m_toPickupWeapon;
	bool m_pickingUpWeapon;

	Weapon* m_thrownWeapon;
	float m_thrownWeaponTime; // time when you're allowed to pickup the previous weapon
	float m_t;
	bool m_timeStart;

	bool m_pressedKey;
};

#endif
