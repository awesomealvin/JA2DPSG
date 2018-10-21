#pragma once
#include "entity.h"
#include "Box2D/Box2D.h"
#include "backbuffer.h"
#include "logmanager.h"

#include <string>
class Box :
	public Entity

{
public:
	Box();
	Box(float width, float height);
	~Box();

	void InitialiseBody(b2World* world, Vector2 position);

	void Draw(BackBuffer& backBuffer);

protected:
	float m_width;
	float m_height;
};

