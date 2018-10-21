#ifndef __HAND_H__
#define __HAND_H__

#include "Melee.h"
class Hand :
	public Melee
{
public:
	Hand();
	~Hand();

	void InitialiseBody(b2World* world, Vector2 position);
	void Draw(BackBuffer& backBuffer);
	void SetPositionClamp(b2Vec2 playerPosition, Vector2 mousePosition, float maxRadius);
	void SetPositionClamp(b2Vec2 position, b2Vec2 aimingPosition, float maxRadius);

	void SetOffsetHandFixture(Vector2 offset);
	b2Vec2 GetOffsetHandPosition() const;

	void SetOffsetWeaponFixture(Vector2 offset);
	b2Vec2 GetOffsetWeaponPosition() const;

	b2Vec2 GetDirection() const; 

protected:
	b2Vec2 m_direction;

};

#endif

