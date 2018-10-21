#pragma once
#include "entity.h"
#include "game.h"
class Ball :
	public Entity
{
public:
	Ball();
	~Ball();

	void Set(float radius);

	void InitialiseBody(b2World* world, Vector2 position);
	void Draw(BackBuffer& backBuffer);

	EntityTypes GetType() const;

protected:
	float m_radius;

};

