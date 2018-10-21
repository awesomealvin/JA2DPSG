#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "character.h"
#include "Hand.h"
#include "PickupSensor.h"
#include "Reticle.h"

class Ball;

class Player :
	public Character
{
public:
	Player();
	~Player();

	void Draw(BackBuffer& backBuffer);
	void Process(float deltaTime);

	bool Initialise(Sprite* sprite, BackBuffer& backBuffer);
	void InitialiseBody(b2World* world, Vector2 position);

	void Pickup();
	void SetWeapon(Weapon* weapon);
	void ThrowWeapon();

	void SetReticleVelocity(Vector2 velocity);
	void SetReticleXVelocity(int x);
	void SetReticleYVelocity(int y);

	void Die();

	EntityTypes GetType() const;

	void OnCollisionBegin(Entity* other, b2Contact* contact);

protected:

	PickupSensor m_pickupSensor;

	Vector2 m_mousePosition;
	Vector2 m_previousMousePosition;

	void SetHandPosition();

	Reticle m_reticle;
};

#endif 

