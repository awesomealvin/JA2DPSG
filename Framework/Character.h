#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "entity.h"

#include "weapon.h"
#include "Hand.h"

class Character :
	public Entity
{
public:
	Character();
	void Draw(BackBuffer& backBuffer);
	void Process(float deltaTime);

	bool Initialise(Sprite* sprite);
	void InitialiseBody(b2World* world, Vector2 position);

	void ApplyMovementForce(float deltaTime);

	void MoveLeft();
	void MoveRight();
	void Jump();
	void Stop();

	void SetBodyCanRotate(bool canRotate);

	void Shoot();
	void SetWeapon(Weapon* weapon);
	bool HasWeapon() const;

	enum MovementStates { MOVELEFT, MOVERIGHT, STATIONARY };
	enum JumpingStates {GROUNDED, JUMPED, DOUBLE_JUMPED};

	float m_lastBulletContactVelocity;
	b2Vec2 m_lastBulletContactWorldPosition;

	void Reset();
	void DropWeapon();

	void SpawnBloodExplosion(int minAmount, int maxAmount);

	void OnCollisionPreSolve(Entity* other, b2Contact* contact, const b2Manifold* oldManifold);

	const float m_handYOffset; // For the shoulders


protected:
	int m_width;
	int m_height;

	float m_movementCircleRadius;

	float m_maxMovementForce;
	float m_jumpForce;
	JumpingStates m_jumpState;

	MovementStates m_movementState;

	Hand m_hand;

	Weapon* m_equippedWeapon;
	bool m_hasWeapon;

	void SetWeaponPosition();

	float m_pickupRange;

	float m_aimingAngle;


	uint16 m_categoryBits;
	uint16 m_maskBits;

	b2Fixture* m_movementFixture;

	b2Fixture* m_hitBoxFixture;

};

#endif // __CHARACTER_H__

