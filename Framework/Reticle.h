#ifndef __RETICLE_H__
#define __RETICLE_H__

#include "Vector2.h"

class BackBuffer;
class Sprite;

class Reticle
{
public:
	Reticle();
	~Reticle();

	void Initialise(Sprite* sprite);

	void SetPosition(Vector2 position);
	void SetVelocity(Vector2 velocity);
	void SetXVelocity(float x);
	void SetYVelocity(float y);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	Vector2 GetPosition() const;

protected:
	Vector2 m_position;
	Vector2 m_velocity;

	int m_width;
	int m_height;

	Sprite* m_pSprite;
};

#endif

